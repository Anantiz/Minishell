/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:05:20 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 13:18:54 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Shall:
		-wait for child
		-listen to child pid return value
		-relay signals to child
	exit
 */
static int	parent_process(t_shell_data *shell_data, t_s_token *node, int pid)
{
	int	wstatus;
	int	ret;

	ret = waitpid(pid, &wstatus, 0);
	if (g_sig == SIGINT)
	{
		kill(pid, SIGINT);
		return (SUCCESS);
	} 
	if (ret == SIGSEGV)
		return (perror("Child SIGSEV"), FAILURE);
	if (ret == -1)
		return (perror("Error in child process"), FAILURE);
	return (SUCCESS);
}

static int	execute_from_path(t_shell_data *shell_data, t_s_token *node)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork() error");
		return (CMD_ERROR_FORK);
	}
	if (pid == 0)
	{
		signal(EOF, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		child_process(shell_data, node, pid);
	}
	else
		return (parent_process(shell_data, node, pid));
}

/*
Fork:
	Child:
		Redirected streams
		Check builtins, if not
		for PATH in all possible_paths:
			execve(PATH, name, args)
		if not found:
			return ERROR
	Parent:
		Wait for child //non-blocking because it has to relay signals
		Relay signals to child
*/
int	execute_command(t_shell_data *shell_data, t_s_token *node)
{
	int		ret;

	ret = check_builtins(shell_data, node);
	if (ret == SUCCESS)
		return (SUCCESS);
	else if (ret == NOT_IN_BUILTINS)
		return (execute_from_path(shell_data, node));
	else
		return (CMD_ERROR_EXEC);
}
