/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:45:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/14 17:19:29 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Any operation token will create a pipe between it's left and right children
		The stdout of the left child will be the write end of the pipe.
		The stdin of the right child will be the read end of the pipe.

	The pipes shall be opened before the execution of the commands.
	The commands shall redirect their stdin and stdout to the pipe ends.
	Any reamining fd shall be closed after the execution of the commands.
*/
int	setup_pipes(t_shell_data *shell_data);

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
			if (init_pipes(node))
				return (PIPE_ERROR);
		}
		node = get_next_node(node);
	}
	return (0);
}
