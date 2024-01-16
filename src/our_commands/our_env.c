/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:13:22 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 17:10:05 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*our_get_env(t_shell_data *shell_data, char *key)
{
	t_env	*env;

	env = shell_data->envp;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	our_env(t_shell_data *shell_data, t_s_token *token)
{
	(void)token;
	(void)shell_data;
	return (SUCCESS);
}
