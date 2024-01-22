/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:11:05 by aurban            #+#    #+#             */
/*   Updated: 2024/01/20 15:30:05 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Depth first search to find the next node to visit
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
	if (node->parent)
	{
		parent = node->parent;
		if (parent->right && parent->right != node)
			return (parent->right);
	}
	return (NULL);
}
