/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:06:01 by loris             #+#    #+#             */
/*   Updated: 2024/02/13 12:17:55 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*   things to handle :
*       -Unclosed quote
		-Leading and Trailing pipes
		-Trailing redir
		-Uneven '&' or "&&&&" and if somehow there is "|||||" , do something with it
*
*/

bool	pre_parsing(char **token_list, int i)
{
	int	count;

	count = 0;
	if (!leading_trailing_op(token_list) \
		|| !deuxrediredesuiteetredireplusspipe(token_list) \
		|| quote_handler(token_list))
		return (false);
	while (token_list[++i])
	{
		if (!unclosed_quote(token_list[i]))
			return (false);
		if (!and_or_checker(token_list[i]))
			return (false);
		if (ft_strlen(token_list[i]) == 1)
		{
			if (ft_strncmp(token_list[i], "(", 1) == 0)
				count++;
			if (ft_strncmp(token_list[i], ")", 1) == 0)
				count--;
		}
	}
	if (count)
		return (false);
	return (true);
}

bool	quote_handler(char **token_list)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (token_list[i])
	{
		quote = 0;
		while (token_list[i][j])
			iter_str_check_quote(ft_chardup(token_list[i][j++]), &quote);
		if (quote)
			return (false);
		i++;
	}
	return (true);
}

bool	leading_trailing_op(char **token_list)
{
	int	len;

	if (scan_token(token_list)->token_type == TK_OP \
		&& !(scan_token(token_list)->data.op.type >= PIPE \
		&& scan_token(token_list)->data.op.type <= REDIR_HEREDOC) \
		&& ft_strncmp(*(token_list), "(", 1))
		return (false);
	len = ft_tablen(token_list);
	if (scan_token(token_list + (len - 1))->token_type == TK_OP \
		&& ft_strncmp(*(token_list + (len - 1)), ")", 1))
		return (false);
	return (true);
}

bool	unclosed_quote(char *token)
{
	int	len;

	len = ft_strlen(token);
	if (token[0] == '\'')
		if (token[len - 1] != '\'')
			return (false);
	if (token[0] == '"')
		if (token[len - 1] != '"')
			return (false);
	return (true);
}

bool	parenthesis_checker(char **token_list)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (token_list[i])
	{
		if (ft_strncmp(token_list[i], "(", 1) == 0)
			count++;
		if (ft_strncmp(token_list[i], ")", 1) == 0)
			count--;
	}
	if (count != 0)
		return (false);
	return (true);
}
