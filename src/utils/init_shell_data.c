/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:04:16 by aurban            #+#    #+#             */
/*   Updated: 2024/02/01 19:05:20 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	No need to free the content of `var` because the pointer changes ownership
*/
static void	create_envp_list(t_shell_data *shell_data, char **envp)
{
	t_env		**head;
	t_env		*var;
	t_pair_char	*pair;

	head = &shell_data->envp;
	while (*envp)
	{
		pair = pair_char_strtok(*envp, '=');
		t_env_add_back(head, t_env_new_node(pair->key, pair->val));
		our_free(pair);
		envp++;
	}
	var = our_get_env(shell_data, "OLDPWD");
	if (!var)
	{
		var = our_get_env(shell_data, "PWD");
		if (var)
			t_env_add_back(head, t_env_new_node(ft_strdup("OLDPWD"), \
				ft_strdup(var->val)));
		else
			t_env_add_back(head, t_env_new_node(ft_strdup("OLDPWD"), \
				unionize_str(getcwd(NULL, 0))));
	}
}

static void	handle_non_existing_path(t_shell_data *shell_data)
{
	t_env		*var;
	char		*pwd;

	var = our_get_env(shell_data, "PATH");
	if (!var)
	{
		var = t_env_new_node(ft_strdup("PATH"), ft_strdup(OG_FUCKING_PATH));
		var->hidden = true;
		t_env_add_back(&shell_data->envp, var);
	}
	var = our_get_env(shell_data, "PWD");
	if (!var)
	{
		pwd = unionize_str(getcwd(NULL, 0));
		var = t_env_new_node(ft_strdup("PWD"), pwd);
		t_env_add_back(&shell_data->envp, var);
		shell_data->our_pwd = ft_strdup(pwd);
	}
}

void	init_shell_data(t_shell_data *shell_data, char **envp)
{
	shell_data->envp = NULL;
	shell_data->our_pwd = NULL;
	create_envp_list(shell_data, envp);
	handle_non_existing_path(shell_data);
	shell_data->root = NULL;
	shell_data->last_command = NULL;
	shell_data->last_pid = 0;
	shell_data->last_wstatus = 0;
}

void	cleanup_shell_data(t_shell_data *shell_data)
{
	rl_clear_history();
	del_tree(shell_data);
	t_env_del_list(&shell_data->envp);
	close(shell_data->stdin_fd);
	close(shell_data->stdout_fd);
}
