/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:12:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 13:24:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* LORIS */
void	del_tree(t_shell_data *shell_data)
{
	(void)shell_data;
}

static int	sesion_routine(t_shell_data *shell_data)
{
	char	*line;
	int		error;

	ft_putstr_fd(SHELL_NAME"$ ", 1);
	line = get_next_line(0 , 0);
	if (!line)
		return (0);
	add_history(shell_data, line);
	error = parse_line(shell_data, line);
	if (error)
		return (PARSING_ERROR);
	if (g_sig == SIGINT) // Display new prompt
		return (SUCCESS);
	error = execute_commands(shell_data);
	if (error)
		return (EXECTION_ERROR);
}

int	session_start(t_shell_data *shell_data)
{
	int		error;

	while (1)
	{
		g_sig = 0;
		error = sesion_routine(shell_data);
		del_tree(shell_data);
		if (error)
			return (error);
	}
}
