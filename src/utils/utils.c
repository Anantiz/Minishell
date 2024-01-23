/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:16:34 by aurban            #+#    #+#             */
/*   Updated: 2024/01/23 11:17:10 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_siblings(t_s_token *node)
{
	t_s_token	*sibling;

	if (node->parent == NULL)
		return (false);
	if (node == node->parent->left)
		sibling = node->parent->right;
	else
		sibling = node->parent->left;
	return (sibling != NULL);
}
