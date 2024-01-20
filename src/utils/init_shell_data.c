/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:04:16 by aurban            #+#    #+#             */
/*   Updated: 2024/01/20 14:35:07 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	No need to free the content of `var` because the pointer changes ownership
*/
static t_env	*create_envp_list(char **envp)
{
	t_env		*head;
	t_pair_char	*var;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		var = pair_char_strtok(envp[i], '=');
		t_env_add_back(&head, t_env_new_node(var->key, var->val));
		free(var);
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

void	cleanup_shell_data(t_shell_data *shell_data)
{
	del_tree(shell_data);
	ft_llstr_del_list(shell_data->get_line_history);
	t_env_del_list(&shell_data->envp);
}
