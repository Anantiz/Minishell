/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:10:04 by aurban            #+#    #+#             */
/*   Updated: 2024/01/29 17:53:43 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
new str, which is the old one, cut at the first dollar,
then we copy var_content, then once done we copy og_str again */
static void	replace_here(char **str, char *var_content, int cut, int var_size)
{
	char	*new_str;
	char	*og_str;
	size_t	i;

	og_str = *str;
	new_str = our_malloc(ft_strlen(og_str) + var_size + 1 * sizeof(char));
	i = 0;
	while (i < cut)
		new_str[i++] = og_str++;
	while (*var_content)
		new_str[i++] = *var_content++;
	while (++og_str)
		new_str[i++] = og_str;
	new_str[i] = '\0';
	free(*str);
	*str = new_str;
}

static char	*expand_here(t_shell_data *shell_data, char *str, int *var_len)
{
	int		i;
	char	*temp;
	char	*ret;

	i = 0;
	while (str[i] && (str[i] != '$' || !ft_is_whitespace(str[i])))
	{
		i++;
	}
	*var_len = i;
	temp = ft_substr(str, 0, i);
	ret = our_get_env(shell_data, temp)->val;
	free(temp);
	return (ret);
}

static char	*expand_variable(t_shell_data *shell_data, t_s_token *node, \
	char **str)
{
	size_t	i;
	int		var_len;
	char	*var_content;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			var_content = expand_here(shell_data, (*str) + 1, &var_len);
			if (var_len > 0)
			{
				replace_here(str, var_content, i, var_len);
				i += var_len - 1;
			}
			free(var_content);
		}
		i++;
	}
}

/*
	If a variable holds just a path it's ok, but if it holds a pipeline it
	shall be an error

	Variables should be expanded for
		-Commands
			-Paths
			-Args
		-File Paths
*/
void	expand_variables(t_shell_data *shell_data, t_s_token *node)
{
	int	i;

	i = 0;
	if (node->token_type == TK_CMD)
	{
		while (node->data.cmd.args[i])
		{
			node->data.cmd.args[i] = expand_variable(shell_data,
				node, &node->data.cmd.args[i]);
			i++;
		}
	}
	else if (node->token_type == TK_FILE)
	{
		node->data.file.file_path = expand_variable(shell_data,
			node, &node->data.file.file_path);
	}
}
