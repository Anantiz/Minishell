/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_file_bs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:28:45 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 13:34:19 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
oooooooooo.
`888'   `Y8b
 888      888  .ooooo.  ooo. .oo.    .ooooo.
 888      888 d88' `88b `888P"Y88b  d88' `88b
 888      888 888   888  888   888  888ooo888
 888     d88' 888   888  888   888  888    .o
o888bood8P'   `Y8bod8P' o888o o888o `Y8bod8P'
*/

static int	get_flags(t_e_op_type type)
{
	if (type == REDIR_IN)
		return (O_RDONLY);
	else if (type == REDIR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (type == REDIR_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (-1);
}

static int	open_file(t_s_file *file, int flags)
{
	file->fd = open(file->file_path, flags, 0644);
	if (file->fd == -1)
	{
		ft_fprintf(2, "%s %s %s\n", SHELL_NAME, file->file_path, \
		strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
	fd == -1 means heredoc
	In heredoc mode, we write to the pipe the data we read from stdin
		-> We do not need to open a file
*/
static int	copy_fd_in_redir_node(t_s_op *redir_node, int fd)
{
	ssize_t	nwrite;

	if (fd == -1)
	{
		nwrite = write(redir_node->pipefd[1], redir_node->heredoc_str, \
			redir_node->heredoc_len);
		redir_node->heredoc_str = NULL;
		close(redir_node->pipefd[1]);
		redir_node->pipefd[1] = PIPE_CLOSED;
		if (nwrite == -1)
			return ((void)ft_fprintf(2, "%s Error : %s\n", SHELL_NAME, \
			strerror(errno)), FAILURE);
	}
	else if (redir_node->type == REDIR_IN)
	{
		redir_node->pipefd[0] = fd;
		redir_node->pipefd[1] = PIPE_CLOSED;
	}
	else if (redir_node->type == REDIR_OUT)
	{
		redir_node->pipefd[0] = PIPE_CLOSED;
		redir_node->pipefd[1] = fd;
	}
	return (SUCCESS);
}

/*
	If heredoc: -> SUCCESS
		do nothing
	else:
		open the file with redir flags
		fd == -1 -> FAILURE
		fd != -1 -> SUCCESS
*/
int	handle_file_bs(t_s_token *file_node)
{
	t_s_token	*redir_node;
	int			flags;

	redir_node = file_node->data.file.redir_nodes[0];
	if (redir_node == NULL)
		redir_node = file_node->data.file.redir_nodes[1];
	if (redir_node == NULL)
		return (FAILURE);
	if (redir_node->data.op.type == REDIR_HEREDOC)
	{
		if (copy_fd_in_redir_node(&redir_node->data.op, -1))
			return (FAILURE);
		return (SUCCESS);
	}
	else
	{
		flags = get_flags(redir_node->data.op.type);
		if (open_file(&file_node->data.file, flags))
			return (FAILURE);
		if (copy_fd_in_redir_node(&redir_node->data.op, \
		file_node->data.file.fd))
			return (FAILURE);
	}
	return (SUCCESS);
}
