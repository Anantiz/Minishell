/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:20:58 by aurban            #+#    #+#             */
/*   Updated: 2024/01/31 15:51:13 by aurban           ###   ########.fr       */
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
	We do not fork() for builtins because we want to modify the shell_data
	In our current model, if we use multiple builtins in a pipeline, and
	exectute them in paralel since they allways dup2 to the standard
	streams but we restore std-streams to default after each command\

	Fuck !
*/
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
			i = (foo_map[i])(shell_data, node);
			return (i);
		}
		i++;
	}
	return (NOT_IN_BUILTINS);
}
