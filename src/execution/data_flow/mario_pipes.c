/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:30:30 by aurban            #+#    #+#             */
/*   Updated: 2024/01/21 14:05:40 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Redirect the commands streams from and into the pipe
int	cmd_redir_streams(t_s_token *cmd_node, t_s_token *redir_node)
{
	if (!redir_node)
		return (SUCCESS);
	if (redir_node->data.op.type == REDIR_IN || (\
		redir_node->data.op.type == PIPE && redir_node->left != cmd_node))
	{
		// Read the pipe
		if (dup2(redir_node->data.op.pipefd[0], STDIN_FILENO) == -1)
			return (perror("dup2() error"), FAILURE);
	}
	else
	{
		// Write to the pipe
		if (dup2(redir_node->data.op.pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2() error"), FAILURE);
	}
}

// Close any pipes that are still open
void	close_all_pipes(t_s_token *node)
{
	while (node)
	{
		if (node->token_type == TK_OP && node->data.op.pipefd[0] != -1)
		{
			if (node->data.op.type >= PIPE && node->data.op.type <= REDIR_HEREDOC)
			{
				close(node->data.op.pipefd[0]);
				close(node->data.op.pipefd[1]);
			}
		}
		node = get_next_node(node);
	}
}

// Init a pipe for any Token that needs it
int open_pipes(t_s_token *node)
{
	if (pipe(node->data.op.pipefd))
	{
		perror("Pipe error");
		return (FAILURE);
	}
	return (SUCCESS);
}
