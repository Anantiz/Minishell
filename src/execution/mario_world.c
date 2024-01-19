/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:45:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 18:18:45 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_file_here_doc(t_s_token *node)
{
	if(dup2(node->parent->data.op.pipefd[0], STDIN_FILENO))
		return (perror("Redir error, Aborting"), FAILURE);
	close(node->parent->data.op.pipefd[0]);
	return (SUCCESS);
}

/*
	Get next TK_FILE token
	Open with flags
	Redirect to
*/
static int	redir_file_file(t_s_token *node, int flags)
/* Not sure about that one */
{
	t_s_token			*file_node;
	int					fd;

	file_node = node;
	while(file_node && file_node->token_type != TK_FILE)
		file_node = get_next_node(file_node);
	if (!file_node)
	{
		ft_fprintf(STDERR_FILENO, SHELL_NAME": syntax error near unexpected"
		"token `newline'\n");
		return (FAILURE);
	}
	fd = open(file_node->data.file.file_path, flags, 0644);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, SHELL_NAME": %s: %s\n", \
			file_node->data.file.file_path, strerror(errno));
		return (FAILURE);
	}
	if (dup2(node->parent->data.op.pipefd[0], fd) == -1)
		return (perror("Redir error, Aborting"), FAILURE);
	close(node->parent->data.op.pipefd[0]);
	return (SUCCESS);
}

/*
Flags for index:
	0: REDIR_OUT
	1: REDIR_IN
	2: REDIR_APPEND
*/

int	redir_file(t_s_token *node)
{
	static const int	redir_flags[3] = REDIR_FLAGS;
	int					i_flags;

	if (node->parent && node->parent->token_type == TK_OP)
	{
		i_flags = 0;
		while (node->parent->data.op.type != (t_e_op_type)\
			(i_flags + REDIR_IN) && i_flags < 4)
			i_flags++;
		if (i_flags == 4)
			return (redir_file_here_doc(node));
		else
			return (redir_file_file(node, redir_flags[i_flags]));
	}
	return (SUCCESS);
}

int	redir_pipe(t_s_token *node)
{
	if (node->parent->token_type == TK_OP && node->parent->data.op.type == PIPE)
	{
		//REDIR output
		if (node->parent->left == node)
		{
			if (dup2(node->parent->data.op.pipefd[1], STDOUT_FILENO) == -1)
			{
				perror("Output redir error, Abort");
				return (FAILURE);
			}
		}
		//REDIR input
		else if (node->parent->right == node)
		{
			if (dup2(node->parent->data.op.pipefd[0], STDIN_FILENO) == -1)
			{
				perror("Input redir error, Abort");
				return (FAILURE);
			}
		}
		close(node->parent->data.op.pipefd[0]);
		close(node->parent->data.op.pipefd[1]);
	}
	return (SUCCESS);
}

/*
Create a pipe that will serve as bridge in between left and right children
*/
static int	init_pipes(t_s_token *node)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror(PIPE_ERROR_MSG_INIT), PIPE_ERROR);
	node->data.op.pipefd[0] = pipefd[0];
	node->data.op.pipefd[1] = pipefd[1];

	// If the parent is a redir_op the current node input will be the parent pipe output
	if (node->parent && node->parent->token_type == TK_OP && \
			(node->data.op.type >= PIPE && \
			node->data.op.type <= REDIR_HEREDOC))
	{
		if (dup2(node->parent->data.op.pipefd[0], pipefd[1]) == -1)
			return (perror("Redir error, Aborting"), FAILURE);
		close(node->parent->data.op.pipefd[0]);
	}
	return (SUCCESS);
}

/*
	Any pipe operation token will create a pipe between it's left and right
	children.
		The stdout of the left child will be the write end of the pipe.
		The stdin of the right child will be the read end of the pipe.

	The pipes shall be opened before the execution of the commands.
	The commands shall redirect their stdin and stdout to the pipe ends.
	Any reamining fd shall be closed after the execution of the commands.
*/
int	setup_pipes(t_shell_data *shell_data)
{
	t_s_token	*node;

	node = shell_data->root;
	while (node)
	{
		if (node->token_type == TK_OP && \
			(node->data.op.type >= PIPE && \
			node->data.op.type <= REDIR_HEREDOC))
		{
			if (init_pipes(node))
				return (PIPE_ERROR);
		}
		node = get_next_node(node);
	}
	return (SUCCESS);
}
