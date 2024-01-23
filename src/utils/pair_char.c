/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:00:38 by aurban            #+#    #+#             */
/*   Updated: 2024/01/23 12:31:49 by aurban           ###   ########.fr       */
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

/*
	Free the malloced content of the pair
	If the content wasn't malloc refer to pair_free(void *pair)
	Free the pair object
*/
void		pair_mfree(void *pair)
{
	if (!pair)
		return ;
	our_free(((t_pair_void *)pair)->first);
	our_free(((t_pair_void *)pair)->second);
	our_free(pair);
}
