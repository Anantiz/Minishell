/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:51:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/30 18:22:23 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Implemented in our_cd2.c
int	cd_path(t_shell_data *shell_data, char *path);

static int	cd_home(t_shell_data *shell_data)
{
	t_env	*home_var;

	home_var = our_get_env(shell_data, "HOME");
	if (!home_var)
	{
		ft_fprintf(2, "cd: HOME not set\n");
		return (FAILURE);
	}
	return (cd_path(shell_data, home_var->val));
}

static int	cd_back(t_shell_data *shell_data)
{
	t_env	*old_pwd;
	char	*path;

	old_pwd = our_get_env(shell_data, "OLDPWD");
	if (!old_pwd)
	{
		ft_fprintf(2, "cd: OLDPWD not set\n");
		return (FAILURE);
	}
	path = ft_strdup(old_pwd->val);
	cd_path(shell_data, path);
	our_free(path);
	our_pwd(shell_data, NULL);
	return (SUCCESS);
}

int	our_cd(t_shell_data *shell_data, t_s_token *node)
{
	if (node->data.cmd.args[1] && node->data.cmd.args[2])
	{
		ft_fprintf(2, "%scd: too many arguments\n", SHELL_NAME);
		return (FAILURE);
	}
	else if (node->data.cmd.args[1] == NULL)
		return (cd_home(shell_data));
	else if (!ft_strcmp(node->data.cmd.args[1], "-"))
		return (cd_back(shell_data));
	else
		return (cd_path(shell_data, node->data.cmd.args[1]));
	return (SUCCESS);
}
