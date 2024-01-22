/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:00:38 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 17:57:02 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Create a pair object cut with the given separator
*/
t_pair_char	*pair_char_strtok(char *str, char sep)
{
	t_pair_char	*ret;
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
	ret->key = ft_substr(str, 0, (cut - str));
	ret->val = ft_substr(cut, 1, ft_strlen(cut) - 1);
	return (ret);
}

void		pair_char_free(t_pair_char *pair)
{
	if (!pair)
		return ;
	our_free(pair->key);
	our_free(pair->val);
	our_free(pair);
}
