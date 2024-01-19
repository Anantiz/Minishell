/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:02:12 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 11:28:10 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void child_cleanup_crew(char **envp, char **paths)
{
	free_double_char(paths);
	free_double_char(envp);
}

static int	redir_pipe(t_s_token *node)
{
	if (node->parent->token_type == TK_OP && node->parent->data.op.type == PIPE)
	{
		//REDIR output
		if (node->parent->left == node)
		{
			if (dup2(node->parent->data.op.pipefd[1], STDOUT_FILENO) == -1)
			{
				perror("Redir in child_process");
				return (FAILURE);
			}
		}
		//REDIR input
		else if (node->parent->right == node)
		{
			if (dup2(node->parent->data.op.pipefd[0], STDIN_FILENO) == -1)
			{
				perror("Redir in child_process");
				return (FAILURE);
			}
		}
		close(node->parent->data.op.pipefd[0]);
		close(node->parent->data.op.pipefd[1]);
	}
	return (SUCCESS);
}

/*
	Look in all paths for the command
		Execute it
		Exit
	else
		ERROR: Not found
*/
void	child_process(t_shell_data *shell_data, t_s_token *node, int pid)
{
	int		i;
	char	**envp;

	if (redir_pipe(node))
		exit(errno);
	process_cmd_paths(shell_data, node);
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
				child_cleanup(envp, node->data.cmd.paths);
				exit(CMD_ERROR_EXEC);
			}
		}
		i++;
	}
	ft_fprintf(2, SHELL_NAME": %s: command not found\n", *node->data.cmd.args);
	child_cleanup_crew(envp, node->data.cmd.paths);
	exit(CMD_ERROR_NOT_FOUND);
}
