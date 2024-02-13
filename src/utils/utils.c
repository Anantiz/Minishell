/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:16:34 by aurban            #+#    #+#             */
/*   Updated: 2024/02/12 20:06:56 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Uses the inner our_pwd for the path
	Replace absolute path with ~ if possible
*/
char	*get_clean_path_shell(t_shell_data *shell_data)
{
	return (get_clean_path(shell_data, ft_strdup(shell_data->our_pwd)));
}

char	*get_clean_path(t_shell_data *shell_data, char *str_path)
{
	char	*str_home;
	t_env	*env_tmp;
	size_t	home_len;

	if (!str_path)
		return (ft_strdup(""));
	env_tmp = our_get_env(shell_data, "HOME");
	if (env_tmp)
		str_home = env_tmp->val;
	else
		str_home = NULL;
	home_len = ft_strlen(str_home);
	if (home_len > 0)
	{
		if (!ft_strncmp(str_path, str_home, home_len))
		{
			ft_replace_str(&str_path, ft_strjoin("~", str_path + home_len));
		}
	}
	return (str_path);
}

bool	is_logop(t_s_token *node)
{
	if (!node)
		return (false);
	return (node->token_type == TK_OP && (node->data.op.type == T_AND
			|| node->data.op.type == T_OR));
}

/*
	if (state == 1)
		x = false;
	else if (state == 2)
		x = true;
	else if (state == 3)
		return (x);*/
bool	dontdoit(int state)
{
	static bool	x = true;

	if (state == 1)
		x = false;
	else if (state == 2)
		x = true;
	else if (state == 3)
		return (x);
	return (x);
}

bool	isbasicredir(t_s_token *node)
{
	if (!node)
		return (false);
	if (node->token_type == TK_OP && (node->data.op.type == REDIR_IN \
	|| node->data.op.type == REDIR_OUT || node->data.op.type == REDIR_APPEND))
		return (true);
	return (false);
}
