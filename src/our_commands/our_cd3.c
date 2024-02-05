/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:07:49 by aurban            #+#    #+#             */
/*   Updated: 2024/02/03 14:30:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_our_long_msg(void)
{
	ft_fprintf(2, "%s cd: The system ran out of memory, so `getcwd()` "
		"failed to return the new path, like fr does `bash` "
		"even handles this ???:%s\n", \
		SHELL_NAME, strerror(errno));
}

static void	create_old_pwd(t_shell_data *shell_data, t_env *cur_pwd_v)
{
	t_env	*old_pwd_v;

	old_pwd_v = t_env_new_node(ft_strdup("OLDPWD"), ft_strdup(""));
	t_env_add_back(&shell_data->envp, old_pwd_v);
	if (cur_pwd_v)
		ft_replace_dupstr(&old_pwd_v->val, cur_pwd_v->val);
}

/*
	This may not be the exact way the real bash does it
	but fuck it, it works
	But like, why the fuck did you even delete the PWD from the first place ?
*/
int	update_pwd(t_shell_data *shell_data, char *path)
{
	t_env	*old_pwd_v;
	t_env	*cur_pwd_v;
	char	*new_pwd_s;

	cur_pwd_v = our_get_env(shell_data, "PWD");
	old_pwd_v = our_get_env(shell_data, "OLDPWD");
	new_pwd_s = unionize_str(getcwd(NULL, 0));
	if (!new_pwd_s)
		return (print_our_long_msg(), FAILURE);
	if (old_pwd_v)
	{
		if (cur_pwd_v)
			ft_replace_dupstr(&old_pwd_v->val, cur_pwd_v->val);
	}
	else
		create_old_pwd(shell_data, cur_pwd_v);
	if (!ft_strcmp(new_pwd_s, "/") && !ft_strcmp(path, "//"))
		ft_replace_dupstr(&new_pwd_s, "//");
	if (cur_pwd_v)
		ft_replace_str(&cur_pwd_v->val, new_pwd_s);
	shell_data->our_pwd = ft_strdup(new_pwd_s);
	return (SUCCESS);
}
