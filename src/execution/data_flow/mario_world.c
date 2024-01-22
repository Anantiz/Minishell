/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:45:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/21 19:43:32 by aurban           ###   ########.fr       */
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

// Close any pipes that are still open
void	close_all_pipes(t_s_token *node)
{
	while (node)
	{
		if (node->token_type == TK_OP && node->data.op.pipefd[0] != -1)
		{
			if (node->data.op.type >= PIPE && node->data.op.type <= REDIR_HEREDOC)
			{
				close(node->data.op.pipefd[0]);
				close(node->data.op.pipefd[1]);
			}
		}
		node = get_next_node(node);
	}
}

// Init a pipe for any Token that needs it
int open_pipes(t_s_token *node)
{
	if (node->data.op.type == PIPE)
	{
		if (pipe(node->data.op.pipefd))
		{
			perror("Pipe error");
			return (FAILURE);
		}
	}
	else
	{
		node->data.op.pipefd[0] = -1;
		node->data.op.pipefd[1] = -1;
	}
	return (SUCCESS);
}

/*
	For any op_type in [pipe, redir_in, redir_out, append, here_doc]
		-Init the node's pipefd
	During exec:
		If a cmd or file direct parent is a logical op, then it shall
		go up the tree until it finds a valid pipefd.
	ATTENTION:
		We do not redirect commands in this current function
		However, we already redirect files in the pipefd
*/
int	init_pipes(t_shell_data *shell_data)
{
	t_s_token	*node;

	node = shell_data->root;
	while (node)
	{
		if (node->token_type == TK_OP)
		{
			if (open_pipes(node))
			{
				fprintf(stderr, "Open Pipe error\n");fflush(stderr);
				close_all_pipes(shell_data->root);
				return (FAILURE);
			}
		}
		else if (node->token_type == TK_FILE)
		{
			if (handle_file_bs(node))
			{
				fprintf(stderr, "Open files error\n");fflush(stderr);
				close_all_pipes(shell_data->root);
				return (FAILURE);
			}
		}
		node = get_next_node(node);
	}
	#ifdef DEBUG
		printf("Pipe setup done\n");
	#endif
	return (SUCCESS);
}
