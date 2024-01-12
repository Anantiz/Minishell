/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:09:25 by aurban            #+#    #+#             */
/*   Updated: 2024/01/12 11:43:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell_data	shell_data;

	// init_shell_data(&shell_data, envp);


	print_shell_intro();
	char		*line;
	size_t		nread;
	while(1)
	{
		printf("Stalin_Shell $> ");
		fflush(stdout);
		
		line = get_next_line(0, 0);
		free(line);
	}
	return (0);
}
