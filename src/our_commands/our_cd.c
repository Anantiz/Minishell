/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:51:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/29 20:56:44 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
   , ,, ,
   | || |    ,/  _____  \.
   \_||_/    ||_/     \_||
     ||       \_| . . |_/
     ||         |  L  |
    ,||         |`==='|
    |>|      ___`>  -<'___
    |>|\    /             \
    \>| \  /  ,    .    .  |
     ||  \/  /| .  |  . |  |
     ||\  ` / | ___|___ |  |     (
  (( || `--'  | _______ |  |     ))  (
(  )\|| (  )\ | - --- - | -| (  ( \  ))
(\/  || ))/ ( | -- - -- |  | )) )  \((
 ( ()||((( ())|         |  |( (( () ) )
*/

/*
	This may not be the exact way the real bash does it
	but fuck it, it works
	But like, why the fuck did you even delete the PWD from the first place ?
*/
static int	update_pwd(t_shell_data *shell_data, t_env *pwd_var, char *path)
{
	t_env	*old_pwd;

	old_pwd = our_get_env(shell_data, "OLDPWD");
	if (old_pwd)
	{
		our_free(old_pwd->val);
		old_pwd->val = pwd_var->val;
	}
	else
		t_env_add_back(&shell_data->envp, \
		t_env_new_node("OLDPWD", getcwd(NULL, 0)));
	pwd_var->val = getcwd(NULL, 0);
	if (pwd_var->val == NULL)
	{
		if (old_pwd)
			pwd_var->val = ft_strdup(old_pwd->val);
		else
			pwd_var->val = ft_strdup("");
		ft_fprintf(2, "cd: %s: %s\n", path, strerror(errno));
		ft_fprintf(1, "cd: %s: %s\n", path, strerror(errno));
		return (FAILURE);
	}
	ft_replace_dupstr(&shell_data->our_pwd, pwd_var->val);
	return (SUCCESS);
}

/*
	When PWD is not set, we need to do some trickery
*/
static int	handle_special_case(t_shell_data *shell_data)
{
	t_env_del_node(&shell_data->envp, our_get_env(shell_data, "OLDPWD"));
	ft_replace_str(&shell_data->our_pwd, getcwd(NULL, 0));
	return (SUCCESS);
}

static int	our_cd_basic(t_shell_data *shell_data, char *path)
{
	t_env	*pwd_var;

	if (chdir(path))
	{
		ft_fprintf(2, "cd: %s: %s\n", path, strerror(errno));
		ft_fprintf(1, "cd: %s: %s\n", path, strerror(errno));
		return (FAILURE);
	}
	pwd_var = our_get_env(shell_data, "PWD");
	if (!pwd_var)
		return (handle_special_case(shell_data));
	if (update_pwd(shell_data, pwd_var, path) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	our_cd(t_shell_data *shell_data, t_s_token *node)
{
	char	*path;
	t_env	*old_pwd;

	if (!ft_strcmp(node->data.cmd.args[1], "-"))
	{
		old_pwd = our_get_env(shell_data, "OLDPWD");
		if (!old_pwd)
		{
			ft_fprintf(2, "cd: OLDPWD not set\n");
			ft_fprintf(1, "cd: OLDPWD not set\n");
			return (FAILURE);
		}
		path = ft_strdup(old_pwd->val);
		our_cd_basic(shell_data, path);
		our_free(path);
		our_pwd(shell_data, NULL);
	}
	else
		our_cd_basic(shell_data, node->data.cmd.args[1]);
	return (SUCCESS);
}
