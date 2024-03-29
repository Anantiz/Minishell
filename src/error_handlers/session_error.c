/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:25:35 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 15:00:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	File is kinda useless lmao
*/

void	display_error(t_shell_data *shell_data, int error)
{
	char	*cmd_name;

	cmd_name = NULL;
	if (error == PARSING_ERROR)
		ft_putstr_fd("Parsing error\n", 2);
	else if (error == EXECTION_ERROR)
	{
		if (shell_data->last_command && shell_data->last_command->args)
		{
			cmd_name = shell_data->last_command->args[0];
			ft_fprintf(2, "Error during last command execution:\n\t`%s`" \
			"  exit status %d\n", cmd_name, shell_data->last_wstatus);
		}
	}
	else if (error == 0)
		ft_putstr_fd("Session ended\n", 2);
}

void	prtshell_err(char *str, char c)
{
	char	*c_str;

	if (c == '>' || c == '<' || c == ' ' || c == '\n')
		c_str = ft_strdup("newline");
	else if (c == ']')
		c_str = ft_strdup("newline");
	else if (c == '|')
		c_str = ft_strdup("||");
	else if (c == '&')
		c_str = ft_strdup("&&");
	else
		c_str = ft_chardup(c);
	ft_fprintf(2, "%s %s `%s'\n", SHELL_NAME, str, c_str);
	our_free(c_str);
}
