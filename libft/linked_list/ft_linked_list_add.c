/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_list_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:35:02 by aurban            #+#    #+#             */
/*   Updated: 2023/12/01 19:58:53 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_nodeint	*ft_llint_data_add_back(t_llint *list, long data, size_t index)
{
	t_nodeint	*node;

	if (!list)
		return (NULL);
	node = malloc(sizeof(t_nodeint));
	if (!node)
		return (NULL);
	node->data = data;
	node->index = index;
	node->next = NULL;
	if (list->last)
	{
		node->previous = list->last;
		list->last->next = node;
	}
	else
		node->previous = NULL;
	list->last = node;
	list->size++;
	if (list->head == NULL)
		list->head = node;
	return (node);
}

t_nodeint	*ft_llint_data_add_front(t_llint *list, long data, size_t index)
{
	t_nodeint	*node;

	if (!list)
		return (NULL);
	node = malloc(sizeof(t_nodeint));
	if (!node)
		return (NULL);
	node->data = data;
	node->index = index;
	node->next = list->head;
	if (list->head != NULL)
		list->head->previous = node;
	if (list->last == NULL)
		list->last = node;
	list->head = node;
	node->previous = NULL;
	list->size++;
	return (node);
}
