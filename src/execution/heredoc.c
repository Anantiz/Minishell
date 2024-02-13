/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:11:03 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 12:56:16 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define EOFERMG "\n%s warning: here-document at line \
%d delimited by end-of-file (wanted `%s'\n"
#define EOF_NO_EOF_ERR_MSG "syntax error near unexpected token `newline'"

static bool	ft_is_eof(char *s1, char *s2, int n)
{
	if (!s1 || !s2)
		return (false);
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
	char		*line;
	char		*ret;

	line = NULL;
	ret = ft_strdup("");
	while ((++line_count) && g_our_sig != SIGINT)
	{
		ft_printf("\033[93m☭ >\033[0m ");
		ft_replace_str(&line, get_next_line(0, 0));
		if (line && g_our_sig != SIGINT)
		{
			if (ft_is_eof(line, eof, ft_strlen(line)))
				break ;
			ft_replace_str(&line, ft_strjoin(line, "\n"));
			ft_replace_str(&ret, ft_strjoin(ret, line));
			*len += ft_strlen(line);
		}
		else if (!line)
			return ((void)ft_printf(EOFERMG, SHELL_NAME, line_count, eof),ret);
	}
	if (ret && ret[0] && ret[1] && ret[ft_strlen(ret) - 1] == '\n')
		ret[ft_strlen(ret) - 1] = '\0';
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

