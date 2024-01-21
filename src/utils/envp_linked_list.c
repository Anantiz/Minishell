/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:14:54 by aurban            #+#    #+#             */
/*   Updated: 2024/01/20 14:36:00 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* new_node */
t_env	*t_env_new_node(char *key, char *value)
{
	t_env	*node;

	node = our_malloc(sizeof(t_env));
	node->key = key;
	node->value = value;
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
	free(node->key);
	free(node->value);
	free(node);
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
		free(node->key);
		free(node->value);
		free(node);
		node = temp;
	}
	root = NULL;
}
