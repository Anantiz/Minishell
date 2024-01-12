/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:07:19 by aurban            #+#    #+#             */
/*   Updated: 2024/01/12 12:07:31 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	***free_triple_char(char ***ccc)
{
	size_t	i;
	size_t	j;

	if (!ccc)
		return (NULL);
	i = 0;
	while (ccc[i])
	{
		j = 0;
		while (ccc[i][j])
			free(ccc[i][j++]);
		free(ccc[i++]);
	}
	free(ccc);
	return (NULL);
}

char	**free_double_char(char **cc)
{
	size_t	i;

	if (!cc)
		return (NULL);
	i = 0;
	while (cc[i])
		free(cc[i++]);
	free(cc);
	return (NULL);
}
