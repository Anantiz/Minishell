/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:09:25 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 13:35:38 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_our_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell_data	shell_data;
	int				session_error;

	(void)argc;
	replace_signals();
	rl_catch_signals = 0;
	restore_std_streams(&shell_data);
	init_shell_data(&shell_data, envp, argv);
	print_shell_intro(NULL, NULL);
	session_error = session_start(&shell_data);
	if (session_error)
		display_error(&shell_data, session_error);
	our_exit(&shell_data, NULL);
}
