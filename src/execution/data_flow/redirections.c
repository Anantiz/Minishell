/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:30:30 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 11:24:12 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Redirect the commands streams from and into the redir_node pipefd
int	cmd_redir_streams(t_s_token *cmd_node, t_s_token *redir_node)
{
	if (!redir_node)
		return (SUCCESS);
	if (redir_node->data.op.type == PIPE && redir_node->left != cmd_node)
	{
		// Read the pipe
		if (dup2(redir_node->data.op.pipefd[0], STDIN_FILENO) == -1)
			return (perror("dup2() error"), FAILURE);
	}
	else
	{
		// Write to the pipe
		if (dup2(redir_node->data.op.pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2() error"), FAILURE);
	}
	return (SUCCESS);
}

/*
	Everytime we redirected the std_streams for a command
	We need to restore them after the command has been executed

	This function is 100% protected *poggers*
*/
int	restore_std_streams(void)
{
	static int	stdin_fd = -1;
	static int	stdout_fd = -1;
/* Initalise it */
	if (stdin_fd == -1)
	{
		stdin_fd = dup(STDIN_FILENO);
		if (stdin_fd == -1)
			return (perror("Initial stdin dup() error"), FAILURE);
		stdout_fd = dup(STDOUT_FILENO);
		if (stdout_fd == -1)
			return (perror("Initial stdout dup() error"), FAILURE);
		fprintf(stderr, "Initial stdin_fd = %d\n", stdin_fd);
		fprintf(stderr, "Initial stdout_fd = %d\n", stdout_fd);
	}
/* Restore */
	else
	{
		if (close(STDIN_FILENO))
			return (perror("Restoring stdin, close() error"), FAILURE);
		if (close(STDOUT_FILENO))
			return (perror("Restoring stdout, close() error"), FAILURE);
		if (dup2(stdin_fd, STDIN_FILENO) == -1)
			return (perror("Restoring stdin, dup2() error"), FAILURE);
		if (dup2(stdout_fd, STDOUT_FILENO) == -1)
			return (perror("Restoring stdout, dup2() error"), FAILURE);
		fprintf(stderr, "Restored standard streams\n");
	}
	return (SUCCESS);
}
