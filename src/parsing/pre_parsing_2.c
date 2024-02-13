/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:51:53 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/13 16:25:08 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Good one
*/
char	quote_handler(char **token_list)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (token_list[i])
	{
		quote = 0;
		j = 0;
		while (token_list[i][j])
			iter_str_check_quote(ft_chardup(token_list[i][j++]), &quote);
		if (quote)
			return (quote);
		i++;
	}
	return (0);
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
			return (false);
		}
		i++;
	}
	return (true);
}

char	and_or_checker(char *token)
{
	if (token[0] == '|')
	{
		if (ft_strlen(token) != 1)
		{
			if (ft_strlen(token) != 2)
				return ('|');
			if (token[1] != '|')
				return ('|');
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

bool	wtfesperluette(char **token_list)
{
	if (ft_tablen(token_list) == 2 && !ft_strncmp(token_list[0], "&", 1))
	{
		if (!ft_strncmp(token_list[1], "+$", 2))
		{
			ft_fprintf(2, "%s syntax error near unexpected token `&'\n", \
			SHELL_NAME);
			return (false);
		}
	}
	return (true);
}
