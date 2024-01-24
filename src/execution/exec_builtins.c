/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:20:58 by aurban            #+#    #+#             */
/*   Updated: 2024/01/23 12:41:15 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_shell_data *shell_data, t_s_token *node)
{
	int							i;
	static const char			*name_map[] = {"cd", "pwd", "env", "echo", \
		"exit", "unset", "export", "red_square", NULL};
	static const t_our_cmd_ptr	foo_map[] = {our_cd, our_pwd, our_env, \
		our_echo, our_exit, our_unset, our_export, print_shell_intro, NULL};

	i = 0;
	while ((t_e_our_commands)i != E_END_CMD)
	{
		if (!ft_strcmp(node->data.cmd.args[0], name_map[i]))
		{
			if (cmd_redir_streams(node) != SUCCESS)
				return (FAILURE);
			return ((foo_map[i])(shell_data, node));
		}
		i++;
	}
	return (NOT_IN_BUILTINS);
}
