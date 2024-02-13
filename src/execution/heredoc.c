/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:11:03 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 10:10:56 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define EOF_ERR_MSG "\n%s warning: here-document at line \
%d delimited by end-of-file (wanted `%s'\n"
#define EOF_NO_EOF_ERR_MSG "syntax error near unexpected token `newline'"

static bool	ft_is_eof(char *s1, char *s2, int n)
{
	while (s1 && s2 && n--)
	{
		if (*s1 != *s2)
		{
			if (n == 0 && *s1 == '\n' && *s2 == '\0')
				return (true);
			return (false);
		}
		s1++;
		s2++;
	}
	return (true);
}

/*
Handle Here_doc

1. While there is no EOF, read and malloc the line (keep it in ram not in file)
	NAIVE 2. When EOF is reached, write the whole thing in the pipe
		{It wont work if there are multiple heredoc, because all
	 	heredoc have to be read before starting the execution }
2. When EOF is reached, store the final string pointer in the redir_node
3. When the command is executed, write the string in the pipe

ISSUES:
	It will use a lot of RAM, so very large here_doc make cause issue
	but who the fuck use heredocs for large inputs anyway
*/
static char	*get_heredoc_str(size_t *len, char *eof)
{
	static int	line_count = 0;
	ssize_t		nread;
	char		*line;
	char		*ret;

	line = NULL;
	ret = ft_strdup("");
	nread = -1;
	while (nread && (++line_count) && g_our_sig != SIGINT)
	{
		ft_printf("");
		ft_replace_str(&line, unionize_str(readline("\033[93m☭ >\033[0m ")));
		nread = ft_strlen(line);
		if (nread && g_our_sig != SIGINT)
		{
			if (ft_is_eof(line, eof, nread))
				break ;
			ft_replace_str(&ret, ft_strjoin(ret, line));
			*len += nread;
		}
		else if (!line || !*line)
			ft_printf(EOF_ERR_MSG, SHELL_NAME, line_count, eof);
	}
	return (our_free(line), ret);
}

int	our_heredoc(t_s_token *redir_node)
{
	t_s_op	*redir_op;

	redir_op = &redir_node->data.op;
	redir_op->heredoc_len = 0;
	if (!redir_node->right)
	{
		redir_op->heredoc_str = ft_strdup("");
		ft_fprintf(2, "%s %s\n", SHELL_NAME, EOF_NO_EOF_ERR_MSG);
		return (FAILURE);
	}
	redir_op->heredoc_str = get_heredoc_str(&redir_op->heredoc_len, \
	redir_node->right->data.file.file_path);
	if (g_our_sig == SIGINT)
	{
		g_our_sig = 0;
		our_free(redir_op->heredoc_str);
		return (FAILURE);
	}
	if (redir_node->right->data.file.single == false)
		expand_this_str(get_shell_data_ptr(NULL), &redir_op->heredoc_str);
	return (SUCCESS);
}

