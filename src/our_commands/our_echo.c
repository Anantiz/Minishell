/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:41:43 by aurban            #+#    #+#             */
/*   Updated: 2024/01/30 10:56:30 by aurban           ###   ########.fr       */
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
	It works, but for consistency, I should always be writing to stdout
	and redirect the stdout to the appropriate fd.
*/

static int	echo_check_end(char *arg, int n_flag, int fd)
{
	if (arg)
	{
		if (write(fd, " ", 1) < 0)
			return (FAILURE);
	}
	else if (n_flag == 1)
	{
		if (write(fd, "\n", 1) < 0)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	our_echo(t_shell_data *shell_data, t_s_token *node)
{
	int			n_flag;
	char		**args;

	(void)shell_data;
	n_flag = 1;
	args = node->data.cmd.args + 1;
	if (args && *args && **args == '-')
	{
		while ((*args)[n_flag] == 'n')
			n_flag++;
		if (n_flag > 1 && ft_is_blank_str(&((*args)[n_flag])))
			args++;
	}
	while (args)
	{
		if (ft_putstr_fd(*args, STDOUT_FILENO) < 0)
			return (FAILURE);
		args++;
		if (echo_check_end(*args, n_flag, STDOUT_FILENO) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
