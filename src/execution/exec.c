/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:39:33 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 12:16:20 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Protocol:
		-1: Init all pipes
		Loop:
			-2: Execute commands  (Monitor global signal and send to children)
				-2.1: Handle redirections
				-2.2: try:
					-Execute from builtins
				else:
					-Execute from absolute path
				else:
					-Execute from path
				-2.3: Handle Errors
				-2.4: Close pipes
			done;
		-3: Cleanup and wait for next command-line
*/

static int exec_commands(t_shell_data *shell_data)
{
	t_s_token	*node;
	int			ret;

	node = shell_data->root;
	int i = 0;
	while (node)
	{
		if (node->token_type == TK_CMD)
		{
			ft_fprintf(2, "Executing node %d: %p\n", i, node);
			ret = exec_one_command(shell_data, node);
			if (ret)
			{
				if (0) // TO DO:
				{
					/*
						Check logical operator to see if
						should exit or do another command
					 */
				}
				else
				{
					printf(CMD_ERROR_EXEC_MSG);
					close_all_pipes(node);
					return (CMD_ERROR_EXEC);
				}
			}
			// restore_std_streams();
			ft_fprintf(2, "Done\n");
		}
		node = get_next_node(node);
		i++;
	}
	ft_fprintf(2, "Execution loop done\n\n");
	return (SUCCESS);
}

int	exec_tree(t_shell_data *shell_data)
{
	ft_fprintf(2, "Executing tree\n");
	if (init_pipes(shell_data))
		return (PIPE_ERROR);
	ft_fprintf(2, "Pipes initialized\n");
	if (exec_commands(shell_data))
		return (EXECTION_ERROR);
	return (SUCCESS);
}
