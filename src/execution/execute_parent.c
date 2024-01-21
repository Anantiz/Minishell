/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:44:49 by aurban            #+#    #+#             */
/*   Updated: 2024/01/21 15:06:02 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Shall:
		-wait for child
		-set last_wstatus
		if child exited normally
			-return SUCCESS
		else
			-return FAILURE
*/
int	parent_process(t_shell_data *shell_data, t_s_token *redir_node, int pid)
{
	int	wstatus;
	int	ret;

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
