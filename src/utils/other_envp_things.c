/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_envp_things.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:14:30 by aurban            #+#    #+#             */
/*   Updated: 2024/01/24 11:12:18 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**t_env_to_double_char(t_env *envp)
{
	char	**ret;
	char	*old;
	t_env	*tmp;
	int		i;

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
		old = ft_strjoin(envp->key, "=");
		ret[i++] = ft_strjoin(old, envp->val);
		our_free(old);
		envp = envp->next;
	}
	ret[i] = NULL;
	return (ret);
}
