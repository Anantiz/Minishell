/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:51:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/14 18:21:52 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	our_cd(t_shell_data *shell_data, t_s_token *token)
{
	char	*pwd;

	pwd = our_get_env("PWD");
	printf("pwd: %s\n", pwd);
	return (0);
}


// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// int main(int argc, char **argv, char **envp)
// {
// 	char *pwd = getenv("PWD");
// 	printf("Og_pwd: %s\n", pwd);
// 	// our_setenv("PWD", "HEYAAYYAAAYY", 1);
// 	chdir("/");
// 	pwd = getenv("PWD");
// 	printf("New_pwd: %s\n", pwd);
// 	return (0);
// }