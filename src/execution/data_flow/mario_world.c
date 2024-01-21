/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:45:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/21 13:42:04 by aurban           ###   ########.fr       */
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
				close_all_pipes(shell_data->root);
				return (FAILURE);
			}
		}
		else if (node->token_type == TK_FILE)
		{
			if (handle_file_bullshit(node))
			{
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
