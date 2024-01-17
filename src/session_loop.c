/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:12:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 16:12:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	session_start(t_shell_data *shell_data)
{
	char	*line;
	int		error;

	error = 0;
	while (1)
	{
		ft_putstr_fd(SHELL_NAME"$ ", 1);
		line = get_next_line(0 , 0);
		if (!line)
			continue ;
		add_history(shell_data, line);
		error = parse_line(shell_data, line);
		if (error)
			return (PARSING_ERROR);
		error = execute_commands(shell_data);
		if (error)
			return (EXECTION_ERROR);
		/* Del tree */
	}
	return (SUCCESS);
}
