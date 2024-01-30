/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:12:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/30 18:45:15 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Hopefully no process will ever return this value :)
#define MAGIC_VALUE_EXIT_SHELL 69420

void	del_tree(t_shell_data *shell_data)
{
	(void)shell_data;
	//to do
	shell_data->root = NULL; // ok for now
}

static char	*get_prompt_str(t_shell_data *shell_data)
{
	char	*clean_path;
	char	*ret;
	t_env	*env_pwd;

	env_pwd = our_get_env(shell_data, "PWD");
	if (!env_pwd)
		clean_path = get_clean_path_shell(shell_data);
	else
		clean_path = get_clean_path(shell_data, ft_strdup(env_pwd->val));
	ret = ft_strjoin("\033[33m", clean_path);
	our_free(clean_path);
	ft_replace_str(&ret, ft_strjoin(SHELL_NAME, ret));
	ft_replace_str(&ret, ft_strjoin(ret, "|\033[93m☭\033[0m "));
	return (ret);
}


static int	sesion_routine(t_shell_data *shell_data)
{
	char	*line;
	char	*prompt_str;
	int		ret;

	prompt_str = get_prompt_str(shell_data);
	line = unionize_str(readline(prompt_str));
	our_free(prompt_str);
	if (!line)
		return (MAGIC_VALUE_EXIT_SHELL);
	if (g_our_sig == SIGINT || !*line || (line[0] == '\n' && line[1] == '\0'))
		return (our_free(line), SUCCESS);
	add_history(line);
	ret = parse_line(shell_data, line);
	our_free(line);
	if (ret)
		return (PARSING_ERROR);
	ret = exec_tree(shell_data);
	if (ret)
		return (EXECTION_ERROR);
	return (SUCCESS);
}

int	session_start(t_shell_data *shell_data)
{
	int		ret;

	while (1)
	{
		g_our_sig = 0;
		shell_data->root = NULL;
		ret = sesion_routine(shell_data);
		del_tree(shell_data);
		if (ret == MAGIC_VALUE_EXIT_SHELL)
			return (SUCCESS);
		if (ret)
			return (ret);
	}
}
