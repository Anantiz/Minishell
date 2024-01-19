/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:02:12 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 18:37:03 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void child_cleanup_crew(char **envp, char **paths)
{
	free_double_char(paths);
	free_double_char(envp);
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

	if (redir_pipe(node))
		exit(errno);
	get_cmd_paths(shell_data, node);
	envp = t_env_to_double_char(shell_data->envp);
	i = 0;
	while (node->data.cmd.paths[i])
	{
		if (access(node->data.cmd.paths[i], X_OK) == 0)
		{
			if (execve(node->data.cmd.paths[i], node->data.cmd.args, envp))
			{
				ft_fprintf(2, SHELL_NAME": %s: %s\n", *node->data.cmd.args, \
					strerror(errno));
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
