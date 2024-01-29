/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:51:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/29 11:52:01 by aurban           ###   ########.fr       */
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

int	our_cd(t_shell_data *shell_data, t_s_token *node)
{
	t_env	*var;

	if (chdir(node->data.cmd.args[1]))
	{
		ft_fprintf(2, "cd: %s: %s\n", node->data.cmd.args[1], strerror(errno));
		return (FAILURE);
	}
	var = our_get_env(shell_data, "PWD");
	our_free(var->val);
	var->val = getcwd(NULL, 0);
	if (var->val == NULL)
	{
		ft_fprintf(2, "cd: %s: %s\n", node->data.cmd.args[1], strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}
