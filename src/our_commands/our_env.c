/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:13:22 by aurban            #+#    #+#             */
/*   Updated: 2024/01/26 14:17:50 by aurban           ###   ########.fr       */
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
	Returns the struct t_env corresponding to the key
	Returns NULL if not found
*/
t_env	*our_get_env(t_shell_data *shell_data, char *key)
{
	t_env	*var;

	if (!key)
		return (NULL);
	var = shell_data->envp;
	while (var)
	{
		if (!ft_strcmp(var->key, key))
			return (var);
		var = var->next;
	}
	return (NULL);
}

/* Simply print envp */
int	our_env(t_shell_data *shell_data, t_s_token *token)
{
	t_env	*var;

	(void)token;
	var = shell_data->envp;
	while (var)
	{
		ft_fprintf(STDOUT_FILENO, "%s=", var->key);
		if (var->val)
			ft_fprintf(STDOUT_FILENO, "%s\n", var->val);
		else
			write(STDOUT_FILENO, "\n", 1);
		var = var->next;
	}
	return (SUCCESS);
}
