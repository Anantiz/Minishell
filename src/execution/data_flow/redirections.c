/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:30:30 by aurban            #+#    #+#             */
/*   Updated: 2024/01/23 12:55:06 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Redir the standard streams with the pipes of the TK_OP
*/
int	cmd_redir_streams(t_s_token *cmd_node)
{
// Obsolete first attempt
	// if (!redir_node || redir_node->token_type != TK_OP || \
	// 	redir_node->data.op.type != PIPE)
	// 	return (SUCCESS);
	// if (redir_node->left != cmd_node)
	// {
	// 	// Read the pipe
	// 	//(it means everytithing read in stdin is actually read from pipe 0)
	// 	if (dup2(redir_node->data.op.pipefd[0], STDIN_FILENO) == -1)
	// 		return (perror("dup2() error"), FAILURE);
	// }
	// else
	// {
	// 	// Write to the pipe
	// 	if (dup2(redir_node->data.op.pipefd[1], STDOUT_FILENO) == -1)
	// 		return (perror("dup2() error"), FAILURE);
	// }

// ACTUALL THING TO DO
	/*
		Find the closest parent that is not a logical op:
			-get it

		If there is one:
			-The command on the right is your output, and this redir_op
				is the pipe to write to , redir your stdout into it and close
				your stdout (it was dup no worry)
			-Put this node on the redir_nodes pair as the second field (cuz output)

		Find whether it has a parent that is also an op but skip logicals_op:
			-The comand on the left of is your input, and this redir_op
				is the pipe to read from , redir your stdin into it and close
				your stdin (it was dup no worry)
			-Put this node on the redir_nodes pair ar the first field (cuz input)
		Note:
			The redir_nodes are stored so that the parent_process will be able
			to send a null byte once the first command is done and clsoe them
	*/
	
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
	}
	return (SUCCESS);
}
