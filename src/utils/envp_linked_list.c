/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:14:54 by aurban            #+#    #+#             */
/*   Updated: 2024/02/01 17:55:12 by aurban           ###   ########.fr       */
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
	RAGE INCOMING:
		SINCE WE HAVE TO CODE IN C, WE CANNOT USE TEMPLATES:
		THUS WE HAVE TO FUCKING CREATE A WHOLE NEW FUNCTION FOR EACH OPERATION
		EVERYTIME WE MAKE A LINKED LIST OF A DIFFERENT DATA

		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	Thx for your attention
*/

/* t_env add_back*/
t_env	*t_env_add_back(t_env **head_, t_env *node)
{
	t_env	*last;

	last = *head_;
	if (!last)
	{
		*head_ = node;
		return (node);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = node;
	return (node);
}

/*
	For compatibility reason, `hidden` is always set to false
	If it should be true, just change it afterwards
*/
t_env	*t_env_new_node(char *key, char *value)
{
	t_env	*node;

	node = our_malloc(sizeof(t_env));
	node->hidden = false;
	node->key = key;
	node->val = value;
	node->next = NULL;
	return (node);
}

void	t_env_del_node(t_env **root, t_env *node_)
{
	t_env	*prev;
	t_env	*node;

	if (!node_)
		return ;
	node = *root;
	prev = NULL;
	while (node != node_ && node)
	{
		prev = node;
		node = node->next;
	}
	if (prev)
		prev->next = node->next;
	if (node == *root)
		*root = (*root)->next;
	if (node != NULL)
	{
		our_free(node->key);
		our_free(node->val);
	}
	our_free(node);
}

void	t_env_del_list(t_env **root)
{
	t_env	*node;
	t_env	*temp;

	if (!root)
		return ;
	node = *root;
	while (node)
	{
		temp = node->next;
		our_free(node->key);
		our_free(node->val);
		our_free(node);
		node = temp;
	}
	root = NULL;
}
