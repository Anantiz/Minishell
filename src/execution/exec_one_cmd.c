/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:05:20 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 14:18:43 by aurban           ###   ########.fr       */
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
	Come back later to handle heredoc

	Parent closes both pipes because it does not need them
	So let's just not open them in the first place
*/
void	parent_close_pipes(t_s_cmd *cmd)
{
	if (cmd->redir_nodes[0])
	{
		if (cmd->redir_nodes[0]->data.op.pipefd[0] != PIPE_CLOSED)
		{
			if (cmd->redir_nodes[0]->data.op.pipefd[0] != -1 && \
			close(cmd->redir_nodes[0]->data.op.pipefd[0]))
				ft_fprintf(2, "%s Pipe error : %s\n", SHELL_NAME, \
				strerror(errno));
			cmd->redir_nodes[0]->data.op.pipefd[0] = PIPE_CLOSED;
		}
		if (cmd->redir_nodes[0]->data.op.pipefd[1] != PIPE_CLOSED)
		{
			if (cmd->redir_nodes[0]->data.op.pipefd[1] != -1 && \
			close(cmd->redir_nodes[0]->data.op.pipefd[1]))
				ft_fprintf(2, "%s Pipe error : %s\n", SHELL_NAME, \
				strerror(errno));
			cmd->redir_nodes[0]->data.op.pipefd[1] = PIPE_CLOSED;
		}
	}
}

static int	execute_from_path(t_shell_data *shell_data, t_s_token *node)
{
	int			pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork() error");
		return (CMD_ERROR_FORK);
	}
	else if (pid == 0)
	{
		cmd_redir_streams(node);
		signal(SIGINT, SIG_DFL);
		signal(SIGKILL, SIG_DFL);
		child_process(shell_data, node);
	}
	shell_data->last_pid = pid;
	shell_data->pid_list[shell_data->pid_count++] = pid;
	parent_close_pipes(&node->data.cmd);
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
