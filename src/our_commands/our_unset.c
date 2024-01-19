/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:08:53 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 16:17:21 by aurban           ###   ########.fr       */
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

int	our_unset(t_shell_data *shell_data, t_s_token *token)
{
	int		i;
	char	**args;
	t_env	*var;

	args = token->data.cmd.args;
	i = -1;
	while (args[++i])
	{
		var = our_get_env(shell_data, args[i]);
		if (!var)
			continue ;
		t_env_del_node(&shell_data->envp, var);
	}
	return (SUCCESS);
}
