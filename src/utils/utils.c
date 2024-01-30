/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:16:34 by aurban            #+#    #+#             */
/*   Updated: 2024/01/30 12:31:11 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_siblings(t_s_token *node)
{
	t_s_token	*sibling;

	if (node->parent == NULL)
		return (false);
	if (node == node->parent->left)
		sibling = node->parent->right;
	else
		sibling = node->parent->left;
	return (sibling != NULL);
}

/*
	Replace absolute path with ~ if possible
	Cleans the path from any useless / and . and ..
	Also removes the last / if there is one
*/
char	*get_clean_path_shell(t_shell_data *shell_data)
{
	char	*str_path;
	char	*str_home;
	t_env	*env_tmp;

	str_path = ft_strdup(shell_data->our_pwd);
	env_tmp = our_get_env(shell_data, "HOME");
	if (env_tmp)
		str_home = env_tmp->val;
	else
		str_home = NULL;
	home_len = ft_strlen(str_home)
	if (home_len > 0)
	{
		if (!ft_strncmp(str_path, str_home, home_len))
		{
			ft_replace_str(&str_path, ft_strjoin("~", str_path + home_len));
		}
	}

}
