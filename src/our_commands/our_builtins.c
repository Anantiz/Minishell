/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:20:58 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 16:18:08 by aurban           ###   ########.fr       */
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

int	check_builtins(t_shell_data *shell_data, t_s_token *node)
{
	int							i;
	static const char			*name_map[] = OUR_COMMANDS_NAMES;
	static const t_our_cmd_ptr	foo_map[] = OUR_COMMANDS_FNC_PTR;

	i = 0;
	while ((t_e_our_commands)i != END_OF_ENUM)
	{
		if (!ft_strcmp(node->data.cmd.args[0], name_map[i]))
		{
			if (redir_pipe(node))
				return (FAILURE);
			return ((foo_map[i])(shell_data, node));
		}
		i++;
	}
	return (NOT_IN_BUILTINS);
}
