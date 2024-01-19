/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:41:43 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 15:15:59 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
oooooooooo.
`888'   `Y8b
 888      888  .ooooo.  ooo. .oo.    .ooooo.
 888      888 d88' `88b `888P"Y88b  d88' `88b
 888      888 888   888  888   888  888ooo888
 888     d88' 888   888  888   888  888    .o
o888bood8P'   `Y8bod8P' o888o o888o `Y8bod8P'
*/

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
