/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:09:25 by aurban            #+#    #+#             */
/*   Updated: 2024/01/17 12:05:36 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell_data	shell_data;
	int				session_error;
	(void)argc;
	(void)argv;

	init_shell_data(&shell_data, envp);
	print_shell_intro(NULL, NULL);

	session_error = session_start(&shell_data);
	display_error(session_error);

	return (clean_shell_data(&shell_data), session_error);
}
