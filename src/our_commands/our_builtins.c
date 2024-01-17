/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:43:23 by aurban            #+#    #+#             */
/*   Updated: 2024/01/17 11:44:39 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_shell_data *shell_data, t_s_token *node)
{
	int							i;
	static const char			*name_map[] = OUR_COMMANDS_NAMES;
	static const t_our_cmd_ptr	foo_map[] = OUR_COMMANDS_FNC_PTR;

	i = 0;
	while ((t_e_our_commands)i != END_OF_ENUM)
	{
		if (ft_strcmp(node->data.cmd.args[0], name_map[i]))
			return ((foo_map[i])(shell_data, node));
		i++;
	}
	return (NOT_IN_BUILTINS);
}
