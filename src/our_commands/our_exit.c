/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:07:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/29 18:53:46 by aurban           ###   ########.fr       */
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

static int	is_valid_integer(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (1);
	return (0);
}

int	our_exit(t_shell_data *shell_data, t_s_token *token)
{
	int	status;

	if (token && is_valid_integer(token->data.cmd.args[1]))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n",
			token->data.cmd.args[1]);
		status = 1;
	}
	else if (token)
		status = ft_atoll(token->data.cmd.args[1]);
	else
		status = 0;
	close_all_pipes(shell_data->root);
	cleanup_shell_data(shell_data);
	ft_putendl_fd("\033[93m☭\033[0m \033[31mСлава герою \
Советского Союза\033[93m☭\033[0m", 1);
	safe_as_fuck_malloc(0, NULL, SAFE_MALLOC_FREE_ALL);
	exit(status);
}
