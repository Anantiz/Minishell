/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:06:01 by loris             #+#    #+#             */
/*   Updated: 2024/02/13 15:55:13 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define ERR_MSG_UNEX "syntax error near unexpected token"
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
	if (!leading_trailing_op(token_list))
		return (false);
	if (!deuxrediredesuiteetredireplusspipe(token_list))
		return (prtshell_err(ERR_MSG_UNEX, '<'), false);
	while (token_list[++i])
	{
		if (quote_handler(token_list))
			return (prtshell_err(ERR_MSG_UNEX, \
			quote_handler(token_list)), false);
		if (!and_or_checker(token_list[i]))
			return (prtshell_err(ERR_MSG_UNEX, '&'), false);
		if (ft_strlen(token_list[i]) == 1)
		{
			if (ft_strncmp(token_list[i], "(", 1) == 0)
				count++;
			if (ft_strncmp(token_list[i], ")", 1) == 0)
				count--;
		}
	}
	if (count)
		return (prtshell_err(ERR_MSG_UNEX, '<'), false);
	return (true);
}

bool	leading_trailing_op(char **token_list)
{
	int			len;
	t_s_token	*node;

	node = scan_token(token_list);
	if (!node)
		return (false);
	if (ft_strlen(token_list[0]) == 1)
		if (ft_strncmp(token_list[0], "&", 1) == 0)
			return (prtshell_err(ERR_MSG_UNEX, '<'), false);
	if (node->token_type == TK_OP \
		&& !(node->data.op.type >= PIPE \
		&& node->data.op.type <= REDIR_HEREDOC) \
		&& ft_strncmp(*(token_list), "(", 1))
		return (prtshell_err(ERR_MSG_UNEX, '<'), false);
	len = ft_tablen(token_list);
	if (scan_token(token_list + (len - 1))->token_type == TK_OP \
		&& ft_strncmp(*(token_list + (len - 1)), ")", 1))
		return (prtshell_err(ERR_MSG_UNEX, '<'), false);
	return (true);
}

// bool	unclosed(char *token)
// {
// 	int	len; // to fix

// 	len = ft_strlen(token);
// 	if (token[0] == '\'')
// 		if (token[len - 1] != '\'')
// 			return (prtshell_err(ERR_MSG_UNEX, '&'), false);
// 	if (token[0] == '"')
// 		if (token[len - 1] != '"')
// 			return (prtshell_err(ERR_MSG_UNEX, '&'), false);
// 	return (true);
// }
