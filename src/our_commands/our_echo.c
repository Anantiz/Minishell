/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:41:43 by aurban            #+#    #+#             */
/*   Updated: 2024/01/23 11:14:14 by aurban           ###   ########.fr       */
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

static int	get_echo_fd(t_s_token *node)
{
	t_s_token	*redir_node;
	int			fd;

	redir_node = get_redir_node(node);
	// print_node(redir_node);
	if (redir_node)
	{
		fd = redir_node->data.op.pipefd[1];
		if (fd == -2) // -2=Here_doc but like , why would you do that?
			fd = STDIN_FILENO;
	}
	else
		fd = STDOUT_FILENO;
	return (fd);
}

static int	echo_check_end(char *arg, int n_flag, int fd)
{
	if (arg)
	{
		if (ft_putchar_fd(' ', fd) == -1)
			return (FAILURE);
	}
	else if (!n_flag)
	{
		if (ft_putchar_fd('\n', fd) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	our_echo(t_shell_data *shell_data, t_s_token *node)
{
	int			fd;
	int			n_flag;
	char		**args;

	(void)shell_data;
	fd = get_echo_fd(node);
	ft_fprintf(2, "\nECHO will write at %d\n", fd);
	n_flag = 0;
	args = node->data.cmd.args + 1;
	while (*args)
	{
		if (!n_flag && !ft_strcmp(*args, "-n"))
		{
			n_flag = 1;
			continue ;
		}
		if (ft_putstr_fd(*(args++), fd) == -1)
			return (FAILURE);
		if (echo_check_end(*args, n_flag, fd) == FAILURE)
			return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}
