/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:45:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/14 15:54:13 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_pipes(t_s_token *node)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (PIPE_ERROR);
	node->data.op.pipefd[0] = pipefd[0];
	node->data.op.pipefd[1] = pipefd[1];
	if (node->data.op.op_type == T_OR || node->data.op.op_type == T_AND)
	{
		if (pipe(pipefd) == -1)
		{
			close(node->data.op.pipefd[0]);
			close(node->data.op.pipefd[1]);
			return (PIPE_ERROR);
		}
		node->data.op.pipefd[0] = pipefd[0];
		node->data.op.pipefd[1] = pipefd[1];
	}
	return (0);
}

int	setup_pipes(t_shell_data *shell_data)
{
	t_s_token	*node;

	node = shell_data->root;
	while (node)
	{
		if (node->token_type == TK_OP)
		{
			init_pipes(node);
		}
	}
	return (0);
}