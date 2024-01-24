/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:12:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/24 16:50:06 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAGIC_VALUE_EXIT_SHELL 69420

static char	*get_prompt_str(t_shell_data *shell_data)
{
	char	*ret;
	char	*old;
	t_env	*env;

	env = our_get_env(shell_data, "PWD");
	if (!env)
		return (ft_strjoin(SHELL_NAME, "|☭ "));
	ret = ft_strjoin(SHELL_NAME, env->val);
	old = ret;
	ret = ft_strjoin(ret, "|☭ ");
	our_free(old);
	return (ret);
}

/* LORIS */
void	del_tree(t_shell_data *shell_data)
{
	(void)shell_data;
}

static int	sesion_routine(t_shell_data *shell_data)
{
	char	*line;
	char	*prompt_str;
	int		ret;

	prompt_str = get_prompt_str(shell_data);
	line = readline(prompt_str);
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
