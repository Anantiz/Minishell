/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:06:01 by loris             #+#    #+#             */
/*   Updated: 2024/02/12 19:00:58 by loris            ###   ########.fr       */
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

bool    pre_parsing(char **token_list)
{
	int i;
	int	count;

	count = 0;
	i = 0;
	while (token_list[i])
	{
		if (unclosed_quote(token_list[i]))
			return(false);
		if (and_or_checker(token_list[i]))
			return (false);
		if (ft_strncmp(token_list[i], "(", 1) == 0)
			count++;
		if (ft_strncmp(token_list[i], ")", 1) == 0)
			count--;
	}
	if (count)
		return (false);
}

bool	function_checker(char *token)
{

}

bool	leading_trailing_op(char **token_list)
{
	int	len;

	if (scan_token(token_list[0])->token_type == TK_OP && !(scan_token(token_list[0])->data.op.type >= PIPE \
		&& scan_token(token_list[0])->data.op.type <= REDIR_APPEND))
		return (false);
	len = ft_tablen(token_list);
	if (scan_token(token_list[len - 1])->token_type == TK_OP)
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
		if (ft_strlen(token) != 2)
			return (false);
		if (token[1] != '|')
			return (false);
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


bool	unclosed_quote(char **token_list)
{

}