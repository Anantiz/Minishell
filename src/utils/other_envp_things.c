/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_envp_things.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:14:30 by aurban            #+#    #+#             */
/*   Updated: 2024/01/17 12:24:34 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**t_env_to_double_char(t_env *envp)
{
	char	**ret;
	t_env	*tmp;
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	tmp = envp;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	ret = our_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp)
	{
		ret[i] = ft_strjoin(envp->key, "=");
		ret[i] = ft_strjoin(ret[i], envp->value);
		envp = envp->next;
		i++;
	}
	return (ret);
}
