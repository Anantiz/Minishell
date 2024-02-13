/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_world_grass_plane.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:45:04 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 10:09:31 by aurban           ###   ########.fr       */
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
		if (node->token_type == TK_OP)
		{
			if (node->data.op.type >= PIPE && node->data.op.type \
				<= REDIR_HEREDOC)
			{
				if (node->data.op.pipefd[0] > STDERR_FILENO)
					close(node->data.op.pipefd[0]);
				if (node->data.op.pipefd[1] > STDERR_FILENO)
					close(node->data.op.pipefd[1]);
				node->data.op.pipefd[0] = -1;
				node->data.op.pipefd[1] = -1;
			}
		}
		node = get_next_node(node);
	}
}

// Init a pipe for any Token that needs it
int	open_pipes(t_s_token *node)
{
	if (node->data.op.type == PIPE || node->data.op.type == REDIR_HEREDOC)
	{
		if (pipe(node->data.op.pipefd))
		{
			ft_fprintf(2, "%sPipe error : %s\n", SHELL_NAME, strerror(errno));
			return (FAILURE);
		}
		if (node->data.op.type == REDIR_HEREDOC)
			if (our_heredoc(node))
				return (FAILURE);
		ft_printf("pipefd[0]=%d pipefd[1]=%d\n", node->data.op.pipefd[0], \
			node->data.op.pipefd[1]);
	}
	else
	{
		node->data.op.pipefd[0] = PIPE_CLOSED;
		node->data.op.pipefd[1] = PIPE_CLOSED;
	}
	return (SUCCESS);
}

int	init_pipes(t_shell_data *shell_data, t_s_token *node)
{
	if (node->token_type == TK_OP)
	{
		node->data.op.did_exec = false;
		if (node->data.op.type >= PIPE && open_pipes(node))
		{
			if (errno)
				ft_fprintf(2, "Open Pipe error :%s\n", strerror(errno));
			close_all_pipes(shell_data->root);
			return (FAILURE);
		}
	}
	else if (node->token_type == TK_CMD)
		find_redir_nodes(node);
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
int	pre_init(t_shell_data *shell_data)
{
	t_s_token	*node;

	node = shell_data->root;
	while (node)
	{
		if (node->token_type == TK_CMD)
			init_cmd_token(shell_data, node);
		if (init_pipes(shell_data, node))
			return (FAILURE);
		if (isbasicredir(node))
		{
			ft_fprintf(2, "\033[31mIN NODE  = %p\033[0m\n", node);
			node = handle_redir_subtree(node);
			ft_fprintf(2, "\033[31mOUT NODE = %p\033[0m\n", node);
		}
		else
			node = get_next_node(node);
	}
	return (SUCCESS);
}
