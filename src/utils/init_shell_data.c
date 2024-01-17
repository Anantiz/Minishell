/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:04:16 by aurban            #+#    #+#             */
/*   Updated: 2024/01/17 14:22:24 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_envp_list(char **envp)
{
	t_env	*head;
	char	**split;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		t_env_add_back(&head, t_env_new_node(split[0], split[1]));
		free(split);
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
