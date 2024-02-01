/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:57:13 by aurban            #+#    #+#             */
/*   Updated: 2024/02/01 19:20:59 by aurban           ###   ########.fr       */
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
static int	update_pwd(t_shell_data *shell_data, char *path)
{
	t_env	*old_pwd_v;
	t_env	*cur_pwd_v;
	char	*new_pwd_s;

	cur_pwd_v = our_get_env(shell_data, "PWD");
	old_pwd_v = our_get_env(shell_data, "OLDPWD");
	new_pwd_s = unionize_str(getcwd(NULL, 0));
	if (!new_pwd_s)
	{
		ft_fprintf(2, "%s cd: The system ran out of memory, so `getcwd()` \
failed to return the new path, like fr does `bash` even handles this ???:%s\n", \
SHELL_NAME, strerror(errno));
		return (FAILURE);
	}
	if (old_pwd_v)
	{
		if (cur_pwd_v)
			ft_replace_dupstr(&old_pwd_v->val, cur_pwd_v->val);
	}
	if (!ft_strcmp(new_pwd_s, "/") && !ft_strcmp(path, "//"))
		ft_replace_dupstr(&new_pwd_s, "//");
	if (cur_pwd_v)
		ft_replace_str(&cur_pwd_v->val, new_pwd_s);
	shell_data->our_pwd = ft_strdup(new_pwd_s);
	return (SUCCESS);
}

static bool	path_is_satanic_inner(char c, bool *was_point)
{
	if (c != '.' && c != '/')
		return (true);
	else if (c == '.')
	{
		if (*was_point == true)
			return (true);
		*was_point = true;
	}
	else if (c == '/')
		*was_point = false;
	return (false);
}

static bool	path_is_satanic(char *path)
{
	bool	was_point;
	bool	quit;

	if (*path++ == '.')
		was_point = true;
	else
		return (false);
	quit = false;
	while (*path)
	{
		quit = path_is_satanic_inner(*path, &was_point);
		if (quit)
			return (false);
		path++;
	}
	return (true);
}

/*
	We have to reproduce bash *feature*
	So take the current shell_data->our_pwd
		-Append the path to it
		ft_strdup() it in PWD (envp) if it exists
	Don't do shrooms kids, or you will code like bash devs
*/
static void	update_satanic_path(t_shell_data *shell_data, char *path)
{
	char	*new_pwd;
	t_env	*pwd_var;

	new_pwd = ft_strjoin(shell_data->our_pwd, "/");
	ft_replace_str(&new_pwd, ft_strjoin(new_pwd, path));
	pwd_var = our_get_env(shell_data, "PWD");
	if (pwd_var)
		ft_replace_dupstr(&pwd_var->val, new_pwd);
	ft_replace_str(&shell_data->our_pwd, new_pwd);
}

/*
	Update the OLDPWD and PWD only if the command succed
	HOWEVER, if it hapens to fail, because the path had only "./" in it
	you shall still update PWD, AND, .//./ also works
	That is satanic
*/
int	cd_path(t_shell_data *shell_data, char *path)
{
	char	*temp;

	if (!path)
		return (FAILURE);
	temp = getcwd(NULL, 0);
	if (path_is_satanic(path) && !temp)
	{
		update_satanic_path(shell_data, path);
		ft_fprintf(2, "cd: error retrieving current directory: "\
		"%s\n", strerror(errno));
		return (FAILURE);
	}
	free(temp);
	if (chdir(path))
	{
		ft_fprintf(2, "cd: %s: %s\n", path, strerror(errno));
		return (FAILURE);
	}
	if (update_pwd(shell_data, path) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
