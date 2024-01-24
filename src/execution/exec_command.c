/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:05:20 by aurban            #+#    #+#             */
/*   Updated: 2024/01/24 18:34:53 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_from_path(t_shell_data *shell_data, t_s_token *node)
{
	int			pid;

	cmd_redir_streams(node);
	pid = fork();
	if (pid == -1)
	{
		perror("fork() error");
		return (CMD_ERROR_FORK);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		child_process(shell_data, node);
	}
	shell_data->last_pid = pid;
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
int	exec_one_command(t_shell_data *shell_data, t_s_token *node)
{
	int			ret;

	ret = check_builtins(shell_data, node);
	if (ret == NOT_IN_BUILTINS)
		return (execute_from_path(shell_data, node));
	return (ret);
}
