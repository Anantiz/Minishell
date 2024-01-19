/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:07:19 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 10:05:01 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_triple_char(char ***ccc)
{
	size_t	i;
	size_t	j;

	if (!ccc)
		return ;
	i = 0;
	while (ccc[i])
	{
		j = 0;
		while (ccc[i][j])
			free(ccc[i][j++]);
		free(ccc[i++]);
	}
	free(ccc);
}

void	free_double_char(char **cc)
{
	size_t	i;

	if (!cc)
		return ;
	i = 0;
	while (cc[i])
		free(cc[i++]);
	free(cc);
}
