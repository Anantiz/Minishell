/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:05:20 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 14:29:38 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NOT_IN_BUILTINS 66

/*
	Look in all paths for the command
		Execute it
		Exit
	else
		ERROR: Not found

*/
static void	child_process(t_shell_data *shell_data, t_s_token *node)
{
	int	i;

	process_cmd_paths(shell_data, node);
	i = 0;
	while (node->data.cmd.paths[i])
	{
		execve(node->data.cmd.paths[i], node->data.cmd.args, shell_data->envp);
		i++;
	}
	ft_fprintf(2, SHELL_NAME": %s: command not found\n", *node->data.cmd.args);
	free_double_char(node->data.cmd.paths);
	exit(CMD_ERROR_NOT_FOUND);
}

/*	Shall:
		-wait for child
		-listen to child pid return value
		-relay signals to child
	exit
 */
static int	parent_process(t_shell_data *shell_data, t_s_token *node)
{
	(void)shell_data;
	(void)node;
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
		child_process(shell_data, node);
	else
		return (parent_process(shell_data, node));
	return (SUCCESS);
}

/* ######################################################################### */
/* ######################################################################### */
/* ######################################################################### */
/*
	Return:
		0: success
		1: not found
		neg: error
*/
static int	check_builtins(t_shell_data *shell_data, t_s_token *node)
{
	if (ft_strcmp(node->data.cmd.args[0] , "cd"))
		return (our_commands(shell_data, node, CD));
	else if (ft_strcmp(node->data.cmd.args[0] , "pwd"))
		return (our_commands(shell_data, node, ECHO));
	else if (ft_strcmp(node->data.cmd.args[0] , "env"))
		return (our_commands(shell_data, node, ENV));
	else if (ft_strcmp(node->data.cmd.args[0] , "echo"))
		return (our_commands(shell_data, node, EXPORT));
	else if (ft_strcmp(node->data.cmd.args[0] , "unset"))
		return (our_commands(shell_data, node, PWD));
	else if (ft_strcmp(node->data.cmd.args[0] , "export"))
		return (our_commands(shell_data, node, UNSET));
	else if (ft_strcmp(node->data.cmd.args[0] , "exit"))
		return (our_commands(shell_data, node, EXIT));
	else
		return (NOT_IN_BUILTINS);
	return (SUCCESS);
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
	if (ret == 0)
		return (SUCCESS);
	else if (ret == NOT_IN_BUILTINS)
		return (execute_from_path(shell_data, node));
	else
		return (CMD_ERROR_EXEC);
}