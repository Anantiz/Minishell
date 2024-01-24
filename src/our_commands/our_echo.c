/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:41:43 by aurban            #+#    #+#             */
/*   Updated: 2024/01/24 18:11:32 by aurban           ###   ########.fr       */
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
		if (ft_putchar_fd(' ', fd) == -1)
			return (FAILURE);
	}
	if (!n_flag)
	{
		if (ft_putchar_fd('\n', fd) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	our_echo(t_shell_data *shell_data, t_s_token *node)
{
	int			n_flag;
	char		**args;

	(void)shell_data;
	n_flag = 0;
	args = node->data.cmd.args + 1;
	while (*args)
	{
		if (!n_flag && !ft_strcmp(*args, "-n"))
		{
			n_flag = 1;
			continue ;
		}
		if (ft_putstr_fd(*(args++), STDOUT_FILENO) == -1)
			return (FAILURE);
		if (echo_check_end(*args, n_flag, STDOUT_FILENO) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
