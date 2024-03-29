/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:01:56 by aurban            #+#    #+#             */
/*   Updated: 2024/01/29 11:28:33 by aurban           ###   ########.fr       */
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

static void	print_shell_intro2(void)
{
	printf("🔴🔴💛💛💛💛💛💛🔴🔴🔴🔴💛💛🔴🔴\n");
	printf("🔴💛💛💛💛🔴💛💛💛🔴🔴🔴💛💛💛🔴");
	printf("    ⣧⢾⣿⣿⣿⣿⣿⣾⣯⣽⣋⠽⢭⣽⣤⡘⢿⣿⣿⣿⣿⣿⣿⣿⣿⠄⣿⣿⣿    ");
	printf("🔴💛💛💛💛🔴💛💛💛🔴🔴🔴💛💛💛🔴\n");
	printf("🔴🔴💛💛🔴🔴🔴💛💛💛🔴🔴🔴💛💛🔴");
	printf("    ⣿⣿⣿⣿⣿⣿⠿⠩⣭⣽⠁⢣⢿⣯⡉⣿⡶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿    ");
	printf("🔴🔴💛💛🔴🔴🔴💛💛💛🔴🔴🔴💛💛🔴\n");
	printf("🔴🔴🔴🔴🔴🔴🔴🔴💛💛💛🔴💛💛💛🔴");
	printf("    ⣿⣿⣿⣿⠿⠁⠄⠈⠋⠈⠄⡈⠁⠒⠌⠊⣃⠹⣿⣿⣿⣿⣿⣏⣻⣿⣿⣿⣿    ");
	printf("🔴🔴🔴🔴🔴🔴🔴🔴💛💛💛🔴💛💛💛🔴\n");
	printf("🔴🔴🔴🔴🔴💛🔴🔴🔴💛💛💛💛💛🔴🔴");
	printf("    ⣿⣿⣿⣷⣶⣤⣤⣶⣿⣿⣿⡿⣿⣷⣤⣄⣤⣠⣼⣿⣿⣿⣿⡟⣿⣿⣿⣿⣿    ");
	printf("🔴🔴🔴🔴🔴💛🔴🔴🔴💛💛💛💛💛🔴🔴\n");
	printf("🔴🔴🔴🔴💛💛💛🔴🔴🔴💛💛💛🔴🔴🔴");
	printf("    ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡁⠸⣿⣿⣿⣿    ");
	printf("🔴🔴🔴🔴💛💛💛🔴🔴🔴💛💛💛🔴🔴🔴\n");
	printf("🔴🔴💛💛💛🔴💛💛💛💛💛💛💛💛🔴🔴");
	printf("    ⣿⣿⡿⠉⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⣷⣿⣿⣿⣿⣿    🔴🔴💛💛💛🔴💛💛💛💛💛💛💛💛🔴🔴\n");
	printf("🔴🔴💛💛🔴🔴🔴💛💛💛🔴🔴💛💛🔴🔴");
	printf("    ⡿⠛   ⠙⢿⣷⣿⣭⡁  ⢉⣿⣿⣿⣿⣿⣿⡟⠄⠹⣿⣿⣿⣿⣿⣿    🔴🔴💛💛🔴🔴🔴💛💛💛🔴🔴💛💛🔴🔴\n");
	printf("🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴");
	printf("    ⡇      ⠙⢿⣷    ⠹⣿⣿⣿⣿⡟    ⢿⣿⣿⣿⣿    ");
	printf("🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴\n");
	printf("_______________________________________________________________\
______________________________________\n\n\n");
}

int	print_shell_intro(t_shell_data *shell_data, t_s_token *node)
{
	(void)shell_data;
	(void)node;
	printf("_______________________________________________________________\
______________________________________\n\n");
	printf("🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴");
	printf("    ⡿⠄⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠞⠛⠁⠄⡼⣿⣿⣿    ");
	printf("🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴🔴\n");
	printf("🔴🔴🔴🔴🔴🔴🔴🔴🔴💛🔴🔴🔴🔴🔴🔴");
	printf("    ⣿⡇⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠙⣦⠐⠠⡥⣿⣿    ");
	printf("🔴🔴🔴🔴🔴🔴🔴🔴🔴💛🔴🔴🔴🔴🔴🔴\n");
	printf("🔴🔴🔴🔴🔴🔴🔴🔴🔴💛💛🔴🔴🔴🔴🔴");
	printf("    ⣿⡇⠄⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⡔⠛⣿⣿    ");
	printf("🔴🔴🔴🔴🔴🔴🔴🔴🔴💛💛🔴🔴🔴🔴🔴\n");
	printf("🔴🔴🔴🔴🔴💛💛💛💛🔴💛💛🔴🔴🔴🔴");
	printf("    ⣿⡇⢰⢏⣤⣦⣤⣍⣉⣿⣿⣿⡟⢋⣁⣤⣤⣤⣈⢻⣿⣿⣿⣿⠚⣯⡄⣿⣿    ");
	printf("🔴🔴🔴🔴🔴💛💛💛💛🔴💛💛🔴🔴🔴🔴\n");
	printf("🔴🔴🔴🔴💛💛💛💛🔴🔴🔴💛💛🔴🔴🔴");
	printf("    ⣿⡇⣾⣿⣉⣀⣠⠅⠄⣽⣿⣿⣇⠈⢈⣉⣩⣐⡙⢿⣿⣿⣿⣿⠤⢿⢱⣿⣿    ");
	printf("🔴🔴🔴🔴💛💛💛💛🔴🔴🔴💛💛🔴🔴🔴\n");
	printf("🔴🔴🔴💛💛💛💛🔴🔴🔴🔴💛💛💛🔴🔴");
	printf("    ⣿⠁⣿⣿⣿⣿⣿⣦⣾⣿⣿⣿⣿⣷⣤⣽⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⠾⣿⣿    ");
	printf("🔴🔴🔴💛💛💛💛🔴🔴🔴🔴💛💛💛🔴🔴\n");
	printf("🔴🔴💛💛💛💛💛💛🔴🔴🔴🔴💛💛🔴🔴");
	printf("    ⡏⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡇⣿⣿    ");
	return (print_shell_intro2(), SUCCESS);
}
