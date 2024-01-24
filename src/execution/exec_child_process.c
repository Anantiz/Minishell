/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:02:12 by aurban            #+#    #+#             */
/*   Updated: 2024/01/24 18:34:33 by aurban           ###   ########.fr       */
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

/* Absolutely not necessary, but it makes some people happy */
static void	child_cleanup_crew(char **envp, char **paths)
{
	free_double_char(paths);
	free_double_char(envp);
	safe_as_fuck_malloc(0, NULL, SAFE_MALLOC_FREE_ALL);
}

/*
	Look in all paths for the command
		Execute it
		Exit
	else
		ERROR: Not found
*/
void	child_process(t_shell_data *shell_data, t_s_token *node)
{
	int		i;
	char	**envp;

	// if (cmd_redir_streams(node))
	// 	exit(errno);
	get_cmd_paths(shell_data, node);
	envp = t_env_to_double_char(shell_data->envp);
	i = 0;
	while (node->data.cmd.paths[i])
	{
		if (access(node->data.cmd.paths[i], X_OK) == 0)
		{
			if (execve(node->data.cmd.paths[i], node->data.cmd.args, envp))
			{
				ft_fprintf(2, "Sub-process failure: %s: %s\n", \
					*node->data.cmd.args, strerror(errno));
				child_cleanup_crew(envp, node->data.cmd.paths);
				exit(CMD_ERROR_EXEC);
			}
		}
		i++;
	}
	ft_fprintf(2, SHELL_NAME": %s: command not found\n", *node->data.cmd.args);
	child_cleanup_crew(envp, node->data.cmd.paths);
	exit(CMD_ERROR_NOT_FOUND);
}
