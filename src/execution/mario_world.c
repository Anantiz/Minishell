/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:45:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/20 17:26:52 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define REDRERRMSG "Redir error, Aborting"

/*
About redir_ops
DEV NOTE:
	What it should do:
		-It has to check if the command about to be executed has a redir at
		some point, if it doesn't then it just runs normally.
		-If it does, it has to open the file and redirect the fd accordingly
		HOWEVER, there is a non null chance that you have to traverse the whole
		tree to find the redir_op, making the whole thing a bit more complicated
	What it actually does:
		-Bro I don't even know what it does anymore
		That's a problem for future me
		Until tomorow
*/

static int	rf_heredoc(t_s_token *node, t_s_token *redir_node)
{
	if(dup2(redir_node->data.op.pipefd[0], STDIN_FILENO))
		return (perror("Here doc "REDRERRMSG), FAILURE);
	close(redir_node->data.op.pipefd[0]);
	return (SUCCESS);
}

/*
	Get next TK_FILE token
	Open with flags
	Redirect to
*/
static int	rf_file(t_s_token *node, t_s_token *redir_node, int flags)
/* Not sure about that one needs review */
{
	t_s_token			*file_node;
	int					fd;

	file_node = node;
	while(file_node && file_node->token_type != TK_FILE)
		file_node = get_next_node(file_node);
	if (!file_node)
	{
		ft_fprintf(STDERR_FILENO, ": syntax error near unexpected"
		"token `newline'\n");
		return (FAILURE);
	}
	fd = open(file_node->data.file.file_path, flags, 0644);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "\nOpen error \"%s\": %s\n", \
			file_node->data.file.file_path, strerror(errno));
		return (FAILURE);
	}

	// If REDIR_OUT
	if (node->parent && node->parent->data.op.type == REDIR_OUT)
	{
		if (dup2(fd, node->parent->data.op.pipefd[1]) == -1)
			return (perror("Redir Out "REDRERRMSG), FAILURE);
		close(node->parent->data.op.pipefd[0]);
	}
	else if (node->parent && node->parent->data.op.type == REDIR_IN)
	{
		if (dup2(fd, node->parent->data.op.pipefd[0]) == -1)
			return (perror("Redir In "REDRERRMSG), FAILURE);
		close(node->parent->data.op.pipefd[1]);
	}
	else
		return (perror("No redir op, wtf"), FAILURE);
	return (SUCCESS);
}

/*
Extremely verbose and robust check so if Satan himself interferes with the
program, it will still work.

	If parent is pipe:
		if sibling is redir_op:
			return sibling
		else:
			if sibling is pipe:
				if (sibling.left is redir_op)
					return sibling.left
				else
					recurse ...

	else if parent is redir_op:
		return parent
	else:
		return NULL
		status = FAILURE
		Like wtf bro, u can't not have a pipe/redir_op as parent
*/
t_s_token	*get_redir_node(t_s_token *cmd_node, int *status)
{
	t_s_token	*redir_node;
	t_e_op_type	p_type;

	*status = 0;
	if (!cmd_node->parent) // It should happen only if the root is a command and it's the only command
		return (NULL);
	p_type = cmd_node->parent->data.op.type;
	if (p_type == TK_OP && (p_type > PIPE && p_type < E_END_OP))
		return (cmd_node->parent); // It means that the parent is a redir_op, no further check needed
	else if (p_type == TK_OP && (p_type <= PIPE && p_type <= T_OR))
	{
		// If we are a right-child and not an OP we are the last token of the command-line
		if (cmd_node->parent->right == cmd_node && cmd_node->token_type != TK_OP)
			return (NULL);
		/*
			Otherwise, we are a left-child and our current sibling is a pipe or a logical op
			We need to follow the tree flow:
				If a node is a redir_op:
					return it
				else if a node is a cmd:
					return (NULL) // It means that output has no redirection
				else it's a pipe or a logic op:
					recurse
				else
					// Wtf did you even do to get here
					*status = FAILURE
					return (NULL)

		*/
	}
	else // Not supposed to happen
	{
		*status = FAILURE;
		return (NULL);
	}
	return (redir_node);
}

/*
	Check if the node has a redir op as parent or sibling
Flags for index:
	0: REDIR_OUT
	1: REDIR_IN
	2: REDIR_APPEND
*/
int	redir_file(t_s_token *node)
{
	static const int	redir_flags[3] = REDIR_FLAGS;
	t_e_op_type			i_flags;
	t_s_token			*redir_node;
	int					status;

	redir_node = get_redir_node(node, &status);
	if (status == FAILURE)
		return (FAILURE);
	if (!redir_node)
		return (SUCCESS);
	i_flags = REDIR_IN;
	while (redir_node->data.op.type != i_flags && i_flags != E_END_OP)
		i_flags++;
	if (i_flags == REDIR_HEREDOC)
		return (rf_heredoc(node, redir_node));
	else
	{
		// fprintf(stderr, "\nRedir file flags %d\n", i_flags - REDIR_IN); fflush(stderr);
		// return (rf_file(node, redir_node, redir_flags[i_flags - REDIR_IN]));
		// Actually you should only redirect the command into the redir_node
		// Redirections of files are handled in TK_FILE
		/*
			After thinking about it, this whole function is probably useless
		*/
	}
	return (SUCCESS);
}

int	redir_pipe(t_s_token *node)
{
	if (node->parent->token_type == TK_OP && node->parent->data.op.type == PIPE)
	{
		//REDIR output
		if (node->parent->left == node)
		{
			if (dup2(node->parent->data.op.pipefd[1], STDOUT_FILENO) == -1)
			{
				perror("Output redir error, Abort");
				return (FAILURE);
			}
		}
		//REDIR input
		else if (node->parent->right == node)
		{
			if (dup2(node->parent->data.op.pipefd[0], STDIN_FILENO) == -1)
			{
				perror("Input redir error, Abort");
				return (FAILURE);
			}
		}
		close(node->parent->data.op.pipefd[0]);
		close(node->parent->data.op.pipefd[1]);
	}
	return (SUCCESS);
}

/*
Create a pipe that will serve as bridge in between left and right children
*/
static int	init_pipes(t_s_token *node)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror(PIPE_ERROR_MSG_INIT), PIPE_ERROR);
	node->data.op.pipefd[0] = pipefd[0];
	node->data.op.pipefd[1] = pipefd[1];

	// If the parent is a redir_op the current node input will be the parent pipe output
	if (node->parent && node->parent->token_type == TK_OP && \
			(node->data.op.type >= PIPE && \
			node->data.op.type <= REDIR_HEREDOC))
	{
		if (dup2(node->parent->data.op.pipefd[0], pipefd[1]) == -1)
			return (perror("Redir error, Aborting"), FAILURE);
		close(node->parent->data.op.pipefd[0]);
	}
	return (SUCCESS);
}

/*
	Any pipe operation token will create a pipe between it's left and right
	children.
		The stdout of the left child will be the write end of the pipe.
		The stdin of the right child will be the read end of the pipe.

	The pipes shall be opened before the execution of the commands.
	The commands shall redirect their stdin and stdout to the pipe ends.
	Any reamining fd shall be closed after the execution of the commands.
*/
int	setup_pipes(t_shell_data *shell_data)
{
	t_s_token	*node;

	node = shell_data->root;
	while (node)
	{
		if (node->token_type == TK_OP && \
			(node->data.op.type >= PIPE && \
			node->data.op.type <= REDIR_HEREDOC))
		{
			if (init_pipes(node))
				return (PIPE_ERROR);
			#ifdef DEBUG
				printf("Pipe created\n");
			#endif
		}
		node = get_next_node(node);
	}
	#ifdef DEBUG
		printf("Pipe setup done\n");
	#endif
	return (SUCCESS);
}
