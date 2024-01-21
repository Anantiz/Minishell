/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_file_bs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:28:45 by aurban            #+#    #+#             */
/*   Updated: 2024/01/21 18:42:39 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Actually this function might just be useless
	because the way the tree is built, the closest redir node
	is always the right one, no need to ignore the pipes
*/
static t_s_token	*fget_redir_node(t_s_token *file_node)
{
	t_s_token	*redir_node;

	redir_node = file_node;
	while (redir_node && redir_node->token_type != TK_OP && \
		(redir_node->data.op.type > PIPE && redir_node->data.op.type \
		< REDIR_HEREDOC))
		redir_node = redir_node->parent;
	if (!redir_node)
	{
		ft_fprintf(2, "No token found, Abort\n");
		return (NULL);
	}
	if (redir_node->data.op.type >= REDIR_IN
		&& redir_node->data.op.type <= REDIR_HEREDOC)
		return (redir_node);
	return (NULL);
}

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
	Redir the file to the right side of the pipe
	So the comnmand will have to redirect the oposite pipefd
*/
static int	redir_filefd_in_op(t_s_op *redir_node, int fd)
{
	if (fd == -1) // There was no reason to create a pipe in the first place, I'll fix that later
	{
		close(redir_node->pipefd[0]);
		close(redir_node->pipefd[1]);
		redir_node->pipefd[0] = -1;
		redir_node->pipefd[1] = -1;
	}
	else if (redir_node->type == REDIR_IN)	// the fd become stdin, which is pipefd[0]
	{
		if (dup2(redir_node->pipefd[1], fd) == -1)
		{
			perror("redir_filefd_in_op(): dup2 error");
			return (FAILURE);
		}
	}
	else									// the fd become stdout, which is pipefd[1]
	{
		if (dup2(redir_node->pipefd[0], fd) == -1)
		{
			perror("redir_filefd_in_op(): dup2 error");
			return (FAILURE);
		}
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

	redir_node = fget_redir_node(file_node);
	fprintf(stderr, "redir_node: %p\n", redir_node);fflush(stderr);
	if (redir_node == NULL)
		return (FAILURE);
	if (redir_node->data.op.type == REDIR_HEREDOC)
	{
		if (redir_filefd_in_op(&redir_node->data.op, -1))
			return (FAILURE);
		return (SUCCESS); // No file to open
	}
	else
	{
		flags = get_flags(redir_node->data.op.type);
		if (open_file(&file_node->data.file, flags))
			return (FAILURE);
		if (redir_filefd_in_op(&redir_node->data.op, file_node->data.file.fd))
			return (FAILURE);
	}
	return (SUCCESS);
}
