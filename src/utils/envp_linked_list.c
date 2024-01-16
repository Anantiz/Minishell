/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:14:54 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 17:46:10 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	RAGE INCOMING:
		SINCE WE HAVE TO CODE IN C, WE CANNOT USE TEMPLATES:
		THUS WE HAVE TO FUCKING CREATE A WHOLE NEW FUNCTION FOR EACH OPERATION
		EVERYTIME WE MAKE A LINKED LIST OF A DIFFERENT DATA
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	Thx for your attention
*/

/* t_env add_back*/
t_env	*t_env_add_back(t_env **head_, t_env *node)
{
	t_env	*head;

	head = *head_;
	if (!head)
	{
		head_ = node;
		return (node);
	}
	while (head->next != NULL)
		head_ = head->next;
	head->next = node;
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

void	t_env_del_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	t_env_del_list(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list->next;
		t_env_del_node(list);
		list = tmp;
	}
	free(list);
}
