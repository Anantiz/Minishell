/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:12:50 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 13:40:32 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Hopefully no process will ever return this value :)
#define MAGIC_VALUE_EXIT_SHELL 69420

static void	del_tree_node(t_s_token *node)
{
	if (!node)
		return ;
	del_tree_node(node->left);
	del_tree_node(node->right);
	if (node->token_type == TK_CMD)
	{
		free_double_char(node->data.cmd.args);
		our_free(node->data.cmd.single);
		node->data.cmd.args = NULL;
		node->data.cmd.single = NULL;
	}
	else if (node->token_type == TK_OP)
	{
		if (node->data.op.pipefd[0] != -1 || node->data.op.pipefd[0] \
		!= PIPE_CLOSED)
			close(node->data.op.pipefd[0]);
		if (node->data.op.pipefd[1] != -1 || node->data.op.pipefd[1] \
		!= PIPE_CLOSED)
			close(node->data.op.pipefd[1]);
	}
	else if (node->token_type == TK_FILE)
		our_free(node->data.file.file_path);
	our_free(node);
}

void	del_tree(t_shell_data *shell_data)
{
	del_tree_node(shell_data->root);
	shell_data->root = NULL;
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

	replace_signals();
	prompt_str = get_prompt_str(shell_data);
	line = unionize_str(readline(prompt_str));
	our_free(prompt_str);
	if (!line)
		return (MAGIC_VALUE_EXIT_SHELL);
	if (!*line || (line[0] == '\n' && line[1] == '\0'))
		return (our_free(line), SUCCESS);
	add_history(line);
	ret = parse_line(shell_data, line);
	our_free(line);
	if (ret || dontdoit(3))
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
		dontdoit(1);
		g_our_sig = 0;
		shell_data->root = NULL;
		shell_data->cmd_count = 0;
		shell_data->pid_count = 0;
		ret = sesion_routine(shell_data);
		del_tree(shell_data);
		if (ret == MAGIC_VALUE_EXIT_SHELL)
			return (SUCCESS);
	}
	return (SUCCESS);
}
