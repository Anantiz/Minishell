/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:11:05 by aurban            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/07 09:54:36 by loris            ###   ########.fr       */
=======
/*   Updated: 2024/02/06 12:15:58 by aurban           ###   ########.fr       */
>>>>>>> 823bc41e0e8fda3b4ff57ba5c4e459ad97184495
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

/*
	Goes up the tree starting from the given node
	returns once a logical operator is found and the
	right child was not already executed
*/
t_s_token	*get_next_logical_op(t_s_token *node)
{
	t_s_token	*prev_node;

	if (!node)
		return (NULL);
	prev_node = node;
	node = node->parent;
	ft_fprintf(2, "\033[33mStarting at node %p\033[0m\n", prev_node);
	ft_fprintf(2, "\033[33mParent is %p\033[0m\n", node);
	while(node)
	{
		if (node->token_type == TK_OP && node->data.op.type < PIPE)
		{
			if (node->right && node->right != prev_node)
				return (node);
			if (node->left && node->data.op.did_exec == false)
				return (node);
		}
		prev_node = node;
		node = node->parent;
	}
	return (NULL);
}
