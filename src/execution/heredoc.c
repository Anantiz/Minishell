/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:11:03 by aurban            #+#    #+#             */
/*   Updated: 2024/02/08 11:42:17 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*line;
	char	*ret;
	ssize_t	nread;

	get_next_line(STDIN_FILENO, 1);
	ret = ft_strdup("");
	nread = -1;
	while (nread)
	{
		ft_printf("\033[93m☭ >\033[0m ");
		line = get_next_line(STDIN_FILENO, 0);
		nread = ft_strlen(line);
		if (nread)
		{
			if (!ft_strcmp(line, eof))
				break ;
			ft_replace_str(&ret, ft_strjoin(ret, line));
			*len += nread;
		}
	}
	get_next_line(STDIN_FILENO, 1);
	ft_fprintf(2, "HEREDOC DONE\n");
	return (ret);
}

void	our_heredoc(t_s_token *redir_node)
{
	t_s_op	*redir_op;
	char	*eof;

	if (redir_node->right)
		eof = redir_node->data.file.file_path;
	else
		eof = ft_strdup("\n");
	redir_op = &redir_node->data.op;
	redir_op->heredoc_len = 0;
	redir_op->heredoc_str = get_heredoc_str(&redir_op->heredoc_len, eof);
	our_free(eof);
}

