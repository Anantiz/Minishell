/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:55:32 by aurban            #+#    #+#             */
/*   Updated: 2024/02/01 13:19:10 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int val, size_t n)
{
	char	*target;
	size_t	i;

	i = 0;
	target = s;
	while (i < n)
	{
		target[i] = val;
		i++;
	}
	return (target);
}
