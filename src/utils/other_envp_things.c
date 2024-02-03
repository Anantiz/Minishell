/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_envp_things.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:14:30 by aurban            #+#    #+#             */
/*   Updated: 2024/02/03 15:31:10 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_size(t_env *envp)
{
	int	ret;

	ret = 0;
	while (envp)
	{
		ret++;
		envp = envp->next;
	}
	return (ret + 1);
}

/*
	IF PATH OR PWD ARE NOT SET, THEY ARE CREATED
*/
char	**t_env_to_double_char(t_env *envp)
{
	char	**ret;
	char	*old;
	int		i;

	ret = our_malloc(sizeof(char *) * (get_env_size(envp) + 1));
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
