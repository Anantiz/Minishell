/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:00:38 by aurban            #+#    #+#             */
/*   Updated: 2024/01/20 14:34:00 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Create a pair object cut with the given separator
*/
t_pair_char	*pair_char_strtok(char *str, char sep)
{
	t_pair_char	*ret;
	size_t		len;
	char		*cut;

	if (!str)
		return (NULL);
	ret = our_malloc(sizeof(t_pair_char));
	cut = ft_strchr(str, sep);
	if (!cut)
	{
		ret->key = ft_strdup(str);
		ret->val = NULL;
		return (ret);
	}
	len = ft_strlen(str);
	ret->key = ft_substr(str, 0, len - (cut - str) - 1);
	ret->val = ft_substr(str, len - (cut - str), len);
	return (ret);
}

void		pair_char_free(t_pair_char *pair)
{
	if (!pair)
		return ;
	free(pair->key);
	free(pair->val);
	free(pair);
}
