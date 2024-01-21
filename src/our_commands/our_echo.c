/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:41:43 by aurban            #+#    #+#             */
/*   Updated: 2024/01/21 21:02:03 by aurban           ###   ########.fr       */
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

int	our_echo(t_shell_data *shell_data, t_s_token *node)
{
	int			fd;
	int			i;
	int			n_flag;
	char		**args;
	t_s_token	*redir_node;

	(void)shell_data;
	fprintf(stderr, "\t");
	redir_node = get_redir_node(node);
	print_node(redir_node);
	if (redir_node)
	{
		fd = redir_node->data.op.pipefd[1];
		if (fd == -2) // Here_doc, but like , why would you do that?
			fd = STDIN_FILENO;
	}
	else
		fd = STDOUT_FILENO;
	fprintf(stderr, "\tECHO will write at %d\n\t\t", fd);
	n_flag = 0;
	args = node->data.cmd.args;
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "-n"))
		{
			n_flag = 1;
			continue ;
		}
		if (ft_putstr_fd(args[i], fd))
			return (FAILURE);
		fprintf(stderr, "%s", args[i]);
		if (!args[i + 1])
		{
			fprintf(stderr, " ");
			if (ft_putchar_fd(' ', fd))
				return (FAILURE);
		}
		i++;
	}
	if (!n_flag)
	{
		if (ft_putchar_fd('\n', fd))
			return (FAILURE);
	}
	fprintf(stderr, "\n");
	return (SUCCESS);
}
