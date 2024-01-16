/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:11:05 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 14:24:41 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_next_node_norm(t_s_token *node, t_s_token **left_sibling)
{
	if (node->parent)
		*left_sibling = node->parent->left;
	else
		*left_sibling = NULL;
}

/*
	Depth first search to find the next node to visit
*/
t_s_token	*get_next_node(t_s_token *node)
{
	t_s_token	*og_node;
	t_s_token	*left_sibling;

	if (!node)
		return (NULL);
	get_next_node_norm(node, &left_sibling);
	og_node = node;
	if (node->left)
		return (node->left);
	if (node->right)
		return (node->right);
	if (node->parent)
	{
		while (node->parent)
		{
			node = node->parent;
			if (node->left && node->left != left_sibling)
				return (node->left);
			if (node->right && node->right != og_node)
				return (node->right);
		}
	}
	return (NULL);
}
