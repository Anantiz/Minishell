/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:09:25 by aurban            #+#    #+#             */
/*   Updated: 2024/01/09 10:14:07 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	foo()
{
	char 		*line;
	t_s_token	*list;

	while (1)
	{
		write(1, "$ROAR> ", 2);
		line = get_line(0);
		list = break_into_list(line);
		free(line);
	}

}

int	main(int argc, char **argv, char **envp)
{
	t_shell_data	shell_data;

	(void)argc;
	(void)argv;
	shell_data.envp = envp;
	return (0);
}
