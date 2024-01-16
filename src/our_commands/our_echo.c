/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:41:43 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 15:02:53 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	our_echo(t_shell_data *shell_data, t_s_token *node)
{
	int 	i;
	int		n_flag;
	char	**args;

	(void)shell_data;
	args = node->data.cmd.args;
	n_flag = 0;
	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "-n"))
		{
			n_flag = 1;
			i++;
			continue ;
		}
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (SUCCESS);
}

/* ************************************************************************** */