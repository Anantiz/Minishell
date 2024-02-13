/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:06:01 by loris             #+#    #+#             */
/*   Updated: 2024/02/13 10:41:53 by lkary-po         ###   ########.fr       */
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

bool	pre_parsing(char **token_list)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	if (!leading_trailing_op(token_list) \
		|| !deuxrediredesuiteetredireplusspipe(token_list))
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

bool	deuxrediredesuiteetredireplusspipe(char **token_list)
{
	int	i;

	i = 0;
	while (token_list[i])
	{
		if (scan_token(token_list + i)->token_type == TK_OP \
			&& token_list[i + 1] && \
			scan_token(&token_list[i + 1])->token_type == TK_OP \
			&& ft_strncmp(token_list[i + 1], "(", 1) \
			&& ft_strncmp(token_list[i + 1], ")", 1) \
			&& ft_strncmp(token_list[i], "(", 1) \
			&& ft_strncmp(token_list[i], ")", 1))
		{
			write(1, "f", 1);
			return (false);
		}
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

bool	and_or_checker(char *token)
{
	int	i;

	i = 0;
	if (token[0] == '|')
	{
		if (ft_strlen(token) != 1)
		{
			if (ft_strlen(token) != 2)
				return (false);
			if (token[1] != '|')
				return (false);
		}
	}
	if (token[0] == '&')
	{
		if (ft_strlen(token) != 2)
			return (false);
		if (token[1] != '&')
			return (false);
	}
	return (true);
}
