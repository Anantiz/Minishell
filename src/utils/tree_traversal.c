/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:11:05 by aurban            #+#    #+#             */
/*   Updated: 2024/02/12 20:07:25 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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
	Depth first search to find the next node to visit
	If we encounter a logical operator, whille climbing up the tree
	we will return NULL, handle this however the fuck you want
*/
t_s_token	*get_next_node(t_s_token *node)
{
	t_s_token	*parent;

	if (!node)
		return (NULL);
	if (node->left)
		return (node->left);
	if (node->right)
		return (node->right);
	while (node->parent)
	{
		parent = node->parent;
		if (parent->right && parent->right != node)
			return (parent->right);
		node = parent;
	}
	return (NULL);
}

t_s_token	*get_next_node_no_op(t_s_token *node)
{
	t_s_token	*parent;

	if (!node || (node->token_type == TK_OP && node->data.op.type < PIPE))
		return (NULL);
	if (node->left)
		return (node->left);
	if (node->right)
		return (node->right);
	while (node->parent)
	{
		parent = node->parent;
		if (parent->token_type == TK_OP && parent->data.op.type < PIPE)
			return (NULL);
		if (parent->right && parent->right != node)
			return (parent->right);
		node = parent;
	}
	return (NULL);
}
