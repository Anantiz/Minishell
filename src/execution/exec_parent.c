/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:44:49 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 14:05:51 by aurban           ###   ########.fr       */
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

static int	print_pretty_error(void)
{
	ft_fprintf(2, "%s: Erro in sub-process %s\n", SHELL_NAME, strerror(errno));
	return (FAILURE);
}

/*	Shall:
		-wait for child
		-set last_wstatus
		if child exited normally
			-return SUCCESS
		else
			-return FAILURE
*/
int	parent_process(t_shell_data *shell_data, t_s_token *cmd_node, int pid)
{
	int	wstatus;
	int	ret;

	wstatus = 0;
	ret = 0;
	if (cmd_node->data.cmd.is_last == true)
	{
		replace_signals_2();
		ret = waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			shell_data->last_wstatus = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			shell_data->last_wstatus = WTERMSIG(wstatus) + 128;
		if (ret == -1)
			return (print_pretty_error());
		else if (wstatus)
			return (FAILURE);
	}
	return (SUCCESS);
}
