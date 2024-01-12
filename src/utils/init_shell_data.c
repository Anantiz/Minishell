/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:04:16 by aurban            #+#    #+#             */
/*   Updated: 2024/01/12 12:43:07 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_history(t_shell_data *shell_data, char *line)
{
	ft_llstr_add_back(shell_data->get_line_history, line);
}

void	init_shell_data(t_shell_data *shell_data, char **envp)
{
	shell_data->get_line_history = ft_llstr_new();
	/* Copy envp */
	shell_data->envp = ft_strdup_double_char(envp);
}

void	clean_shell_data(t_shell_data *shell_data)
{
	ft_llstr_del_list(shell_data->get_line_history);
	free_double_char(shell_data->envp);
}
