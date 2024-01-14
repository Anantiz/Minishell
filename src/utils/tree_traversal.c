/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:11:05 by aurban            #+#    #+#             */
/*   Updated: 2024/01/14 17:11:17 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Depth first search to find the next node to visit
*/
t_s_token	*get_next_node(t_s_token *node)
{
	if (node->left)
		return (node->left);
	if (node->right)
		return (node->right);
	if (node->parent)
	{
		while (node->parent)
		{
			node = node->parent;
			if (node->right)
				return (node->right);
		}
	}
	return (NULL);
}
