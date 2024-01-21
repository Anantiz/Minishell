/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:12:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/21 15:17:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAGIC_VALUE_SUCCESS 69420

/* LORIS */
void	del_tree(t_shell_data *shell_data)
{
	(void)shell_data;
}

static int	sesion_routine(t_shell_data *shell_data)
{
	char	*line;
	int		error;

	line = readline(SHELL_NAME"$ ");
	if (!line)
		return (MAGIC_VALUE_SUCCESS);
	add_history(line);
	error = parse_line(shell_data, line);
	free(line);
	if (error)
		return (PARSING_ERROR);
	if (our_g_sig == SIGINT) // Display new prompt
		return (SUCCESS);
	error = exec_tree(shell_data);
	if (error)
		return (EXECTION_ERROR);
	return (SUCCESS);
}

int	session_start(t_shell_data *shell_data)
{
	int		error;

	while (1)
	{
		our_g_sig = 0;
		shell_data->root = NULL;
		error = sesion_routine(shell_data);
		del_tree(shell_data);
		if (error == MAGIC_VALUE_SUCCESS)
			return (SUCCESS);
		if (error)
			return (error);
	}
}
