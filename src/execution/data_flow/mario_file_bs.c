/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_file_bs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:28:45 by aurban            #+#    #+#             */
/*   Updated: 2024/01/23 16:44:24 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		perror("open_file(): Open error");
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
	fd == -1 means heredoc
	Screw the pipes, we just close them and put fd instead
	Pieps were never opened in the first place
	*vilain laugh*
*/
static int	copy_fd_in_redir_node(t_s_op *redir_node, int fd)
{
	if (fd == -1)
	{
		// Here_doc
		redir_node->pipefd[0] = -2;
		redir_node->pipefd[1] = -2;
	}
	else if (redir_node->type == REDIR_IN)	// Reads from file, so fd becomes pipefd[0]
	{
		redir_node->pipefd[0] = fd;
		redir_node->pipefd[1] = -1;
	}
	else									// Write to file, so fd becomes pipefd[1]
	{
		redir_node->pipefd[0] = -1;
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

	find_redir_nodes(file_node);
	redir_node = file_node->data.file.redir_nodes[0];
	if (redir_node == NULL)
		redir_node = file_node->data.file.redir_nodes[1];
	if (redir_node == NULL)
		return (FAILURE);
	if (redir_node->data.op.type == REDIR_HEREDOC)
	{
		if (copy_fd_in_redir_node(&redir_node->data.op, -1))
			return (FAILURE);
		return (SUCCESS); // No file to open
	}
	else
	{
		flags = get_flags(redir_node->data.op.type);
		if (open_file(&file_node->data.file, flags))
			return (FAILURE);
		if (copy_fd_in_redir_node(&redir_node->data.op, file_node->data.file.fd))
			return (FAILURE);
	}
	return (SUCCESS);
}
