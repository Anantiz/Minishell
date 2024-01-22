/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:41:43 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 11:11:49 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
