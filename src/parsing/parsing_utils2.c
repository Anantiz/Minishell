/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:45:11 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/13 12:30:33 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_o_parenthesis(char *token)
{
	if (!token || !(*token))
		return (false);
	if (*token == '(')
		return (true);
	return (false);
}

bool	ft_is_c_parenthesis(char *token)
{
	if (!token || !(*token))
		return (false);
	if (*token == ')')
		return (true);
	return (false);
}

t_s_token	*parse_cmd(char **token_list, int token_count, \
	t_s_token *parent_node)
{
	t_s_token	*node;

	if (!token_list)
		return (NULL);
	if (ft_is_parenthesis(token_list))
	{
		del_parenthesis(token_list, token_count);
		node = parse_expression(token_list, ft_tablen(token_list), parent_node);
	}
	else
	{
		node = scan_token(token_list);
		if (!node)
			return (NULL);
		node->parent = parent_node;
		node->right = NULL;
		node->left = NULL;
	}
	return (node);
}

/* Advance until an op is found, then trim the trailing white spaces */
int	ft_cmdlen(char	*cmd)
{
	int		i;

	i = 0;
	while (ft_is_op(cmd[i]) == false && cmd[i])
		i++;
	i--;
	while (i > -1 && ft_is_sep(cmd[i]) == true)
		i--;
	return (i + 1);
}

char	**custom_sliping_jimmy(char *str)
{
	char	**return_array;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	return_array = our_malloc(sizeof(char *) * 3);
	return_array[2] = NULL;
	while (str[i] && str[i] != ' ')
		i++;
	return_array[0] = ft_substr(str, 0, i);
	while (str[i] == ' ')
		i++;
	return_array[1] = ft_substr(str, i, ft_strlen(&str[i]));
	return (return_array);
}
