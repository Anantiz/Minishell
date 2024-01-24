/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:12:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 16:57:27 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAGIC_VALUE_EXIT_SHELL 69420

/* LORIS */
void	del_tree(t_shell_data *shell_data)
{
	(void)shell_data;
}

static int	sesion_routine(t_shell_data *shell_data)
{
	char	*line;
	int		ret;

	line = readline(SHELL_NAME"$ ");
	if (g_our_sig == SIGINT)
		return (our_free(line), SUCCESS);
	if (!line)
		return (MAGIC_VALUE_EXIT_SHELL);
	add_history(line);
	ret = parse_line(shell_data, line);
	our_free(line);
	if (ret)
		return (PARSING_ERROR);
	ret = exec_tree(shell_data);
	if (ret)
		return (EXECTION_ERROR);
	return (SUCCESS);
}

int	session_start(t_shell_data *shell_data)
{
	int		ret;

	while (1)
	{
		g_our_sig = 0;
		shell_data->root = NULL;
		ret = sesion_routine(shell_data);
		del_tree(shell_data);
		if (ret == MAGIC_VALUE_EXIT_SHELL)
			return (SUCCESS);
		if (ret)
			return (ret);
	}
}
