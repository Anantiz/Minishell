/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 12:30:30 by aurban            #+#    #+#             */
/*   Updated: 2024/01/24 11:58:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_parent_redir(t_s_token *child, t_s_token **parent)
{
	*parent = child->parent;
	while ((*parent))
	{
		if ((*parent)->token_type == TK_OP)
		{
			if ((*parent)->data.op.type < PIPE)
				(*parent) = NULL;
			break ;
		}
		(*parent) = (*parent)->parent;
	}
}

/*
	This function dont't handle here-docs for now
	But here-docs are a special case of redir_in, I might implement it as a
	redir_in in disguise, or as a special case, I don't know yet
*/
static void	assign_redir_nodes(t_s_token *cmd_node, t_s_token *redir_nodes[2])
{
	if (!redir_nodes[1])
	{
		if (cmd_node == redir_nodes[0]->left)
		{
			if (redir_nodes[0]->data.op.type != REDIR_IN)
			{
				cmd_node->data.cmd.redir_nodes[0] = NULL; // We do not redirect our stdin
				cmd_node->data.cmd.redir_nodes[1] = redir_nodes[0]; // This is now were we redirect stdout
			}
			else
			{
				cmd_node->data.cmd.redir_nodes[0] = redir_nodes[0]; // Our stdin will be the file fd
				cmd_node->data.cmd.redir_nodes[1] = NULL; // We do not redirect our stdout
			}
		}
		else
		{
			if (redir_nodes[0]->data.op.type != REDIR_IN)
			{
				cmd_node->data.cmd.redir_nodes[0] = redir_nodes[0]; // This is were we get our stdin
				cmd_node->data.cmd.redir_nodes[1] = NULL; // We do not redirect our stdout, we are the last args of the pipeline
			}
			else
			{
				cmd_node->data.cmd.redir_nodes[0] = NULL; // We do not redirect our stdin, we are a file lol
				cmd_node->data.cmd.redir_nodes[1] = redir_nodes[0]; // This is where the file fd is stored, where the command will read
			}
		}
	}
	else // B: there is a second parent, we are in the middle of a pipeline
	{
		cmd_node->data.cmd.redir_nodes[0] = redir_nodes[1]; // This is were we get our stdin
		cmd_node->data.cmd.redir_nodes[1] = redir_nodes[0]; // This is now were we redirect stdout
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
*/
int	cmd_redir_streams(t_s_token *cmd_node)
{
	t_s_cmd	*cmd;

	cmd = &cmd_node->data.cmd;
	if (cmd->redir_nodes[0])
	{
		if (dup2(cmd->redir_nodes[0]->data.op.pipefd[0], STDIN_FILENO) == -1)
			return (perror("Redirecting STD-IN, dup2() error"), FAILURE);
	}
	if (cmd->redir_nodes[1])
	{
		if (dup2(cmd->redir_nodes[1]->data.op.pipefd[1], STDOUT_FILENO) == -1)
			return (perror("Redirecting STD-OUT, dup2() error"), FAILURE);
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

	if (stdin_fd == -1)
	{
		stdin_fd = dup(STDIN_FILENO);
		if (stdin_fd == -1)
			return (perror("Initial stdin dup() error"), FAILURE);
		stdout_fd = dup(STDOUT_FILENO);
		if (stdout_fd == -1)
			return (perror("Initial stdout dup() error"), FAILURE);
	}
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

/*
Cas chiants:

1.$< file cmd == cmd < file
2.$file > file does Nothing
3.$<file does nothing

4.0$<< eof file \ Invalid
4.1$<< eof cmd \ Ok
*/

/*
Wildcard subtilities
$ cmd > *
Ca fait qq chose si Il y a un seul fichier dans le dossier
autrement : "bash: *: ambiguous redirect"
*/