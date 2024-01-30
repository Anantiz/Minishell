/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_envp_things.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:14:30 by aurban            #+#    #+#             */
/*   Updated: 2024/01/30 11:01:04 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_missing_envp(t_shell_data *shell_data, char **ret, \
bool path_pwd[2])
{
	int	i;

	i = 0;
	if (!path_pwd[0])
		ret[i++] = ft_strdup(OG_FUCKING_PATH);
	if (!path_pwd[1])
		ret[i++] = ft_strdup(shell_data->our_pwd);
	return (i);
}

static int	get_env_size(t_env *envp, bool path_pwd[2])
{
	int	i;

	path_pwd[0] = false;
	path_pwd[1] = false;
	i = 3;
	while (envp)
	{
		if (!ft_strcmp(envp->key, "PATH"))
		{
			path_pwd[0] = true;
			i--;
		}
		else if (!ft_strcmp(envp->key, "PWD"))
		{
			path_pwd[1] = true;
			i--;
		}
		if (envp->val != NULL && envp->val[0] != '\0')
			i++;
		envp = envp->next;
	}
	return (i);
}

/*
	IF PATH OR PWD ARE NOT SET, THEY ARE CREATED
*/
char	**t_env_to_double_char(t_shell_data *shell_data, t_env *envp)
{
	char	**ret;
	char	*old;
	int		i;
	bool	path_pwd[2];

	ret = our_malloc(sizeof(char *) * (get_env_size(envp, path_pwd)));
	i = add_missing_envp(shell_data, ret, path_pwd);
	while (envp)
	{
		if (!ft_is_blank_str(envp->val))
		{
			old = ft_strjoin(envp->key, "=");
			ret[i++] = ft_strjoin(old, envp->val);
			our_free(old);
		}
		envp = envp->next;
	}
	ret[i] = NULL;
	return (ret);
}
