/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:04:16 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 17:57:58 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_envp_list(char **envp)
{
	t_env	*head;
	int		i;
	char	*key;
	char	*value;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		key = ft_strdup(envp[i]);
		value = ft_strdup(envp[i]);
		ft_env_add_back(&head, ft_env_new_node(key, value));
		i++;
	}
	return (head);
}

void	add_history(t_shell_data *shell_data, char *line)
{
	ft_llstr_add_back(shell_data->get_line_history, line);
}

void	init_shell_data(t_shell_data *shell_data, char **envp)
{
	shell_data->get_line_history = ft_llstr_new();
	shell_data->envp = create_envp_list(envp);
}

void	clean_shell_data(t_shell_data *shell_data)
{
	ft_llstr_del_list(shell_data->get_line_history);
	t_env_del_list(shell_data->envp);
}
