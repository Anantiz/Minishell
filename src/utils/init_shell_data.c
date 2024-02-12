/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:04:16 by aurban            #+#    #+#             */
/*   Updated: 2024/02/12 20:23:53 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	No need to free the content of `var` because the pointer changes ownership
*/
static void	create_envp_list(t_shell_data *shell_data, char **envp)
{
	t_env		**head;
	t_pair_char	*pair;

	head = &shell_data->envp;
	while (*envp)
	{
		pair = pair_char_strtok(*envp, '=');
		t_env_add_back(head, t_env_new_node(pair->key, pair->val));
		our_free(pair);
		envp++;
	}
}

static void	handle_non_existing_path(t_shell_data *shell_data, char *argv[])
{
	t_env		*var;

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
		var = t_env_new_node(ft_strdup("PWD"), unionize_str(getcwd(NULL, 0)));
		t_env_add_back(&shell_data->envp, var);
		shell_data->our_pwd = ft_strdup(ft_strdup(var->val));
	}
	var = our_get_env(shell_data, "SHLVL");
	if (!var)
		t_env_add_back(&shell_data->envp, \
		t_env_new_node(ft_strdup("SHLVL"), ft_strdup("1")));
	var = our_get_env(shell_data, "_");
	if (!var)
		t_env_add_back(&shell_data->envp, \
		t_env_new_node(ft_strdup("_"), ft_strdup(argv[0])));
}

void	init_shell_data(t_shell_data *shell_data, char **envp, char *argv[])
{
	shell_data->envp = NULL;
	shell_data->our_pwd = NULL;
	create_envp_list(shell_data, envp);
	handle_non_existing_path(shell_data, argv);
	shell_data->root = NULL;
	shell_data->last_command = NULL;
	shell_data->last_pid = 0;
	shell_data->last_wstatus = 0;
	get_shell_data_ptr(shell_data);
}

void	cleanup_shell_data(t_shell_data *shell_data)
{
	rl_clear_history();
	del_tree(shell_data);
	t_env_del_list(&shell_data->envp);
	close(shell_data->stdin_fd);
	close(shell_data->stdout_fd);
}
