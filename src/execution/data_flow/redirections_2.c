/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:44:08 by aurban            #+#    #+#             */
/*   Updated: 2024/02/01 12:14:41 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	First we find the redir_nodes
	Then we redirect our std-streams using the pipefd of the redir_nodes

	Here doc not done yet
*/
int	cmd_redir_streams(t_s_token *cmd_node)
{
	t_s_cmd	*cmd;

	cmd = &cmd_node->data.cmd;
	if (cmd->redir_nodes[0] \
		&& cmd->redir_nodes[0]->data.op.type != REDIR_HEREDOC)
	{
		close(cmd->redir_nodes[0]->data.op.pipefd[1]);
		if (dup2(cmd->redir_nodes[0]->data.op.pipefd[0], STDIN_FILENO) == -1)
		{
			ft_fprintf(2, "Node: %p: ", cmd_node);
			ft_fprintf(2, "Redirecting STD-IN, dup2() error : %s : fd=%d\n", \
			strerror(errno), cmd->redir_nodes[0]->data.op.pipefd[0]);
			return (FAILURE);
		}
		close(cmd->redir_nodes[0]->data.op.pipefd[0]);
	}
	if (cmd->redir_nodes[1] \
		&& cmd->redir_nodes[1]->data.op.type != REDIR_HEREDOC)
	{
		close(cmd->redir_nodes[1]->data.op.pipefd[0]);
		if (dup2(cmd->redir_nodes[1]->data.op.pipefd[1], STDOUT_FILENO) == -1)
		{
			ft_fprintf(2, "Node %p: ", cmd_node);
			ft_fprintf(2, "Redirecting STD-OUT, dup2() error : %s : fd=%d\n", \
			strerror(errno), cmd->redir_nodes[1]->data.op.pipefd[1]);
			return (FAILURE);
		}
		close(cmd->redir_nodes[1]->data.op.pipefd[1]);
	}
	return (SUCCESS);
}

/* **************************************************************************
	Everytime we redirected the std_streams for a command
	We need to restore them after the command has been executed
*/
int	restore_std_streams(t_shell_data *shell_data)
{
	static int	stdin_fd = -1;
	static int	stdout_fd = -1;

	if (stdin_fd == -1)
	{
		stdin_fd = dup(STDIN_FILENO);
		if (stdin_fd == -1)
			return (perror("Initial stdin dup() error"), FAILURE);
		stdout_fd = dup(STDOUT_FILENO);
		if (stdout_fd == -1)
			return (perror("Initial stdout dup() error"), FAILURE);
		shell_data->stdin_fd = stdin_fd;
		shell_data->stdout_fd = stdout_fd;
	}
	else
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		if (dup2(stdin_fd, STDIN_FILENO) == -1)
			return (perror("Restoring stdin, dup2() error"), FAILURE);
		if (dup2(stdout_fd, STDOUT_FILENO) == -1)
			return (perror("Restoring stdout, dup2() error"), FAILURE);
	}
	return (SUCCESS);
}
