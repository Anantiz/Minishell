/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:44:08 by aurban            #+#    #+#             */
/*   Updated: 2024/01/29 11:52:19 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	If you are the last node, do not redirect your output to the second parent,
	 as it is actually the second parent of your input, you have none
	If our first parent is the left child of the second parent,
	then we write to the second parent and read from first parent
		-> This is because we are both reading from a file, and redirecting our input
		to an other command/file
		if we were being piped from an other command there would only be a single
	If our first parent is the right child of the second parent,
	we read from the second parent and write to the first parent
*/
static void do_redir_2(t_s_token *cmd_node, t_s_token **redir_nodes)
{
	if (redir_nodes[0] == redir_nodes[1]->right)
	{
		if (cmd_node == redir_nodes[0]->right)
		{
			cmd_node->data.cmd.redir_nodes[0] = redir_nodes[0]; // The measured second parent is not related to use because we are the last command
			cmd_node->data.cmd.redir_nodes[1] = NULL; // We do not redirect our stdout, we are the last args of the pipeline/subpipline
		}
		else
		{
			cmd_node->data.cmd.redir_nodes[0] = redir_nodes[1]; // This is were we get our stdin
			cmd_node->data.cmd.redir_nodes[1] = redir_nodes[0]; // We do not redirect our stdout, we are the last args of the pipeline/subpipline
		}
	}
	else // What even is this case
	{
		ft_fprintf(2, "Weird ass thing that should not happen just happened\n");
		cmd_node->data.cmd.redir_nodes[0] = redir_nodes[0]; // This is were we get our stdin
		cmd_node->data.cmd.redir_nodes[1] = redir_nodes[1]; // This is now were we redirect stdout
	}
}

static void	do_redir_1_1(t_s_token *cmd_node, t_s_token **redir_nodes)
{
	if (redir_nodes[0]->data.op.type == REDIR_IN \
		|| redir_nodes[0]->data.op.type == REDIR_HEREDOC)
	{
		cmd_node->data.cmd.redir_nodes[0] = NULL; // We do not redirect our stdin, we are a file lolc
		cmd_node->data.cmd.redir_nodes[1] = redir_nodes[0]; // This is where the file fd is stored, where the command will read
	}
	else
	{
		cmd_node->data.cmd.redir_nodes[0] = redir_nodes[0]; // This is were we get our stdin
		cmd_node->data.cmd.redir_nodes[1] = NULL;
	}
}

/*
	If there is only one redir_parent, then it means: there are only
	two sub_token either piping two commands, or redir a cmd to/from
	a file. We handle the case where we are the first or second(last)
	command to be executed. We also inverse the order if we are
	reading/writing to a file because dup2() will treat redir_nodes
	order the same way we do for pipes .It kinda is stupid to not
	directly use the pipefd, but It's clearer this way
	and allow for better modularity
*/
static void	do_redir_1(t_s_token *cmd_node, t_s_token **redir_nodes)
{
		if (cmd_node == redir_nodes[0]->left)
		{
			if (redir_nodes[0]->data.op.type == REDIR_IN \
				|| redir_nodes[0]->data.op.type == REDIR_HEREDOC)
			{
				cmd_node->data.cmd.redir_nodes[0] = redir_nodes[0]; // Our stdin will be the file fd
				cmd_node->data.cmd.redir_nodes[1] = NULL; // We do not redirect our stdout
			}
			else
			{
				cmd_node->data.cmd.redir_nodes[0] = NULL; // We do not redirect our stdin
				cmd_node->data.cmd.redir_nodes[1] = redir_nodes[0]; // This is now were we redirect stdout
			}
		}
		else
			do_redir_1_1(cmd_node, redir_nodes);
}

/*
	This function dont't handle here-docs for now
	But here-docs are a special case of redir_in, I might implement it as a
	redir_in in disguise, or as a special case, I don't know yet
*/
void	assign_redir_nodes(t_s_token *cmd_node, t_s_token *redir_nodes[2])
{
	if (!redir_nodes[1])
		do_redir_1(cmd_node, redir_nodes);
	else // B: there is a second parent, we are in the middle of a pipeline
		do_redir_2(cmd_node, redir_nodes);
}
