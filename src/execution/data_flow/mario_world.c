/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:45:04 by aurban            #+#    #+#             */
/*   Updated: 2024/02/03 10:14:05 by aurban           ###   ########.fr       */
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
			our_heredoc(node);
		ft_printf("pipefd[0]=%d pipefd[1]=%d\n", node->data.op.pipefd[0], \
			node->data.op.pipefd[1]);
	}
	else
	{
		node->data.op.pipefd[0] = -690;
		node->data.op.pipefd[1] = -4200;
	}
	return (SUCCESS);
}

int	init_pipes_iner_loop(t_shell_data *shell_data, t_s_token *node)
{
	if (node->token_type == TK_OP)
	{
		if (open_pipes(node))
		{
			ft_fprintf(2, "Open Pipe error\n");
			close_all_pipes(shell_data->root);
			return (FAILURE);
		}
	}
	else if (node->token_type == TK_FILE)
	{
		find_redir_nodes(node);
		if (handle_file_bs(node))
		{
			ft_fprintf(2, "Open files error\n");
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
int	init_pipes(t_shell_data *shell_data)
{
	t_s_token	*node;

	node = shell_data->root;
	while (node)
	{
		/* FIXING HERE NOW but shall do elsewhere later*/
		if (node->token_type == TK_CMD)
		{
			shell_data->cmd_count++;
			node->data.cmd.is_last = false;
			if (node->right == NULL)
			{
				node->data.cmd.is_last = true;
				if (node->parent && node->parent->right != node)
					node->data.cmd.is_last = false;
			}
		}
		if (init_pipes_iner_loop(shell_data, node))
			return (FAILURE);
		node = get_next_node(node);
	}
	return (SUCCESS);
}
