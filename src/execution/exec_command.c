/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:05:20 by aurban            #+#    #+#             */
/*   Updated: 2024/01/21 15:02:26 by aurban           ###   ########.fr       */
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

/*
	Look for the first redir op
		-If none found, return NULL
		-Else return the node
*/
t_s_token	*get_redir_node(t_s_token *cmd_node)
{
	t_s_token	*redir_node;

	redir_node = cmd_node->parent;
	while (redir_node)
	{
		if (redir_node->token_type == TK_OP && \
			redir_node->data.op.type >= PIPE)
			return (redir_node);
		redir_node = redir_node->parent;
	}
	return (NULL);
}

static int	execute_from_path(t_shell_data *shell_data, t_s_token *node, \
	t_s_token *redir_node)
{
	int			pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork() error");
		return (CMD_ERROR_FORK);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		child_process(shell_data, node, redir_node);
	}
	return (parent_process(shell_data, node, redir_node, pid));
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
	t_s_token	*redir_node;
	int			ret;

	redir_node = get_redir_node(node);
	ret = check_builtins(shell_data, node, redir_node);
	if (ret == NOT_IN_BUILTINS)
		return (execute_from_path(shell_data, node, redir_node));
	return (ret);
}
