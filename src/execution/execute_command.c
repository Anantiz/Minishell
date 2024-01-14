/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:05:20 by aurban            #+#    #+#             */
/*   Updated: 2024/01/14 18:13:22 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Return:
		0: success
		pos: not found
		neg: error
*/
static int	check_builtins(t_shell_data *shell_data, t_s_token *node)
{
	if (ft_strcmp(node->data.cmd.args[0] , "cd"))
		our_commands(CD, node);
	else if (ft_strcmp(node->data.cmd.args[0] , "pwd"))
		our_commands(ECHO, node);
	else if (ft_strcmp(node->data.cmd.args[0] , "env"))
		our_commands(ENV, node);
	else if (ft_strcmp(node->data.cmd.args[0] , "echo"))
		our_commands(EXPORT, node);
	else if (ft_strcmp(node->data.cmd.args[0] , "unset"))
		our_commands(PWD, node);
	else if (ft_strcmp(node->data.cmd.args[0] , "export"))
		our_commands(UNSET, node);
	else if (ft_strcmp(node->data.cmd.args[0] , "exit"))
		our_commands(EXIT, node);
	else
		return (1);
	return (0);
}

/*
	Has to look for each parameter of the commands,
	compare strings with existing variables, replace if found
*/
int	execute_command(t_shell_data *shell_data, t_s_token *node)
{
	(void)shell_data;
	(void)node;
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
	return (0);
}