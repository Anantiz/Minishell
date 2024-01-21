/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:30:30 by aurban            #+#    #+#             */
/*   Updated: 2024/01/21 15:32:32 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Redirect the commands streams from and into the redir_node pipefd
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
	return (SUCCESS);
}
