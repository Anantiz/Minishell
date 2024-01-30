/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:04:16 by aurban            #+#    #+#             */
/*   Updated: 2024/01/29 20:53:44 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	No need to free the content of `var` because the pointer changes ownership
*/
static t_env	*create_envp_list(t_shell_data *shell_data, char **envp)
{
	t_env		*head;
	t_pair_char	*var;
	int			i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		var = pair_char_strtok(envp[i], '=');
		t_env_add_back(&head, t_env_new_node(var->key, var->val));
		if (!ft_strcmp(var->key, "PWD"))
		{
			shell_data->our_pwd = ft_strdup(var->val);
			t_env_add_back(&head, t_env_new_node(ft_strdup("OLDPWD"), \
			ft_strdup(var->val)));
		}
		our_free(var);
		i++;
	}
	return (head);
}

void	init_shell_data(t_shell_data *shell_data, char **envp)
{
	shell_data->envp = create_envp_list(shell_data, envp);
	shell_data->last_command = NULL;
	shell_data->last_wstatus = 0;
	shell_data->last_pid = 0;
}

void	cleanup_shell_data(t_shell_data *shell_data)
{
	rl_clear_history();
	del_tree(shell_data);
	t_env_del_list(&shell_data->envp);
	close(shell_data->stdin_fd);
	close(shell_data->stdout_fd);
}
