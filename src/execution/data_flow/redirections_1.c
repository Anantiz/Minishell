/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:30:30 by aurban            #+#    #+#             */
/*   Updated: 2024/01/29 12:01:41 by aurban           ###   ########.fr       */
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

static void	get_parent_redir(t_s_token *child, t_s_token **parent)
{
	*parent = child->parent;
	while ((*parent))
	{
		if ((*parent)->token_type == TK_OP)
		{
			if ((*parent)->data.op.type < PIPE)
				(*parent) = NULL;
			return ;
		}
		(*parent) = (*parent)->parent;
	}
}

/*
Note that: if we encounter logical ops, they did break the pipelines, so we
treat them as roots of a sub tree

	The tree architecture is that we always redirect our output to the first
	redirect_op we find, and we always take our input from the parent of this
	very same redirect_op

Find the first redir_parent
Find the second redir_parent
A:	If this redirect_op has no second parent, then it means:
		Case1. (We are the left_child): We are the first command
		Case2. (We are the right_child): There are only 2 commands
				We are the last command and wrting to stdout
B:	If it has a parent:
		-Our first parent is the one we will write to
		-Our second parent is the one we will read from
*/
void	find_redir_nodes(t_s_token *cmd_node)
{
	t_s_token	*redir_nodes[2];

	cmd_node->data.cmd.redir_nodes[0] = NULL;
	cmd_node->data.cmd.redir_nodes[1] = NULL;
	get_parent_redir(cmd_node, &redir_nodes[0]);
	if (!redir_nodes[0])
		return ;
	get_parent_redir(redir_nodes[0], &redir_nodes[1]);
	assign_redir_nodes(cmd_node, redir_nodes);
}

/*
	First we find the redir_nodes
	Then we redirect our std-streams using the pipefd of the redir_nodes

	Here doc not really accurate, it works but don't handle eof
*/
int	cmd_redir_streams(t_s_token *cmd_node)
{
	t_s_cmd	*cmd;

	cmd = &cmd_node->data.cmd;
	ft_fprintf(2, "\t%s node[0]: %p\n",cmd_node->data.cmd.args[0], cmd->redir_nodes[0]);
	ft_fprintf(2, "\t%s node[1]: %p\n", cmd_node->data.cmd.args[0],cmd->redir_nodes[1]);
	if (cmd->redir_nodes[0] \
		&& cmd->redir_nodes[0]->data.op.type != REDIR_HEREDOC)
	{
		if (dup2(cmd->redir_nodes[0]->data.op.pipefd[0], STDIN_FILENO) == -1)
		{
			ft_fprintf(2, "\t%s redir_node pipefd[0]: %d, pipefd[1]: %d\n",cmd_node->data.cmd.args[0], cmd->redir_nodes[0]->data.op.pipefd[0], cmd->redir_nodes[1] != NULL ? cmd->redir_nodes[1]->data.op.pipefd[1] : -69);
			return (perror("Redirecting STD-IN, dup2() error"), FAILURE);
		}
		ft_fprintf(2, "\t%s iClosing: %d\n", cmd_node->data.cmd.args[0],cmd->redir_nodes[0]->data.op.pipefd[0]);
		cmd->redir_nodes[0]->data.op.pipefd[0] = -10;
	}
	if (cmd->redir_nodes[1] \
		&& cmd->redir_nodes[1]->data.op.type != REDIR_HEREDOC)
	{
		if (dup2(cmd->redir_nodes[1]->data.op.pipefd[1], STDOUT_FILENO) == -1)
			return (perror("Redirecting STD-OUT, dup2() error"), FAILURE);
		ft_fprintf(2, "\t%s oClosing: %d\n",cmd_node->data.cmd.args[0], cmd->redir_nodes[1]->data.op.pipefd[1]);
		close(cmd->redir_nodes[1]->data.op.pipefd[1]);
		cmd->redir_nodes[1]->data.op.pipefd[1] = -10;
	}
	return (SUCCESS);
}

/*
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
