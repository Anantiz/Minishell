/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:44:49 by aurban            #+#    #+#             */
/*   Updated: 2024/01/23 15:32:42 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The parent process needs a way to know if the executiong node
	is writing or reading, and additionally, i just thought of it,
	but what If I read and write to two pipes at the same time?
	*AAAAAAAAAAA* -professionaly
*/

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

	(void)cmd_node;
	ret = waitpid(pid, &wstatus, 0);
	if(WIFEXITED(wstatus))
		shell_data->last_wstatus = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		shell_data->last_wstatus = WTERMSIG(wstatus) + 128;

	if (ret == -1)
		return (perror("Error in child process"), FAILURE);
	if (wstatus)
		return (FAILURE);
	return (SUCCESS);
}
