/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:16:42 by aurban            #+#    #+#             */
/*   Updated: 2024/02/06 19:06:37 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_last_subtree(t_shell_data *shell_data)
{
	while (shell_data->skip < shell_data->pid_count)
	{
		if (shell_data->pid_list[shell_data->skip] != -69)
			waitpid(shell_data->pid_list[shell_data->skip], NULL, 0);
		shell_data->skip++;
	}
}
