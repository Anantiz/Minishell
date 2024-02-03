/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:10:04 by aurban            #+#    #+#             */
/*   Updated: 2024/02/03 15:33:25 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

*/
static void	replace_here(char **str, char *var_str, int cut, int key_len)
{
	char	*new_str;
	char	*og_str;
	int		i;

	og_str = *str;
	new_str = our_malloc((ft_strlen(og_str) + ft_strlen(var_str) + 2) * \
		sizeof(char));
	i = 0;
	while (i < cut)
		new_str[i++] = *og_str++;
	while (key_len-- > -1)
		og_str++;
	while (*var_str)
	{
		new_str[i++] = *var_str;
		var_str++;
	}
	while (*og_str)
		new_str[i++] = *og_str++;
	new_str[i] = '\0';
	ft_replace_str(str, new_str);
}

/*
	Get the variable name
	Search for it in the env
	If found, return the content
	Else return NULL
*/
static char	*get_the_var(t_shell_data *shell_data, char *str, int *key_len)
{
	int		i;
	char	*var_name;
	t_env	*ret;

	i = 0;
	while (str[i] && !(str[i] == '$' || ft_isspace(str[i]) ||
			str[i] == '=' || str[i] == '\'' || str[i] == '\"'))
	{
		i++;
	}
	*key_len = i;
	var_name = ft_substr(str, 0, i);
	ft_fprintf(2, "var_name: %s\n", var_name);
	if (ft_strcmp(var_name, "?") == 0)
	{
		our_free(var_name);
		return (ft_itoa(shell_data->last_wstatus));
	}
	ret = our_get_env(shell_data, var_name);
	our_free(var_name);
	if (!ret)
		return (NULL);
	return (ft_strdup(ret->val));
}

/*
	Searches for a $ in the string
		If found:
			-Get the content of the variable
*/
static void	expand_this_str(t_shell_data *shell_data, char **str)
{
	size_t	i;
	char	*var_str;
	int		offset;
	int		key_len;

	i = 0;
	offset = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			var_str = get_the_var(shell_data, &(*str)[i + 1], &key_len);
			if (var_str)
			{
				replace_here(str, var_str, i + offset, key_len);
				offset += ft_strlen(var_str);
			}
			our_free(var_str);
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
	int i;

	i = 0;
	if (node->token_type == TK_CMD)
	{
		while (node->data.cmd.args[i])
		{
			expand_this_str(shell_data, &node->data.cmd.args[i++]);
		}
	}
	else if (node->token_type == TK_FILE)
	{
		expand_this_str(shell_data, &node->data.file.file_path);
	}
}
