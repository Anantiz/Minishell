/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:41:29 by loris             #+#    #+#             */
/*   Updated: 2024/02/10 16:51:12 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*get_cmd(char *line, int *i)
{
	int		len_cmd;
	char	*ret;

	len_cmd = ft_cmdlen(line);
	ret = ft_substr(line, 0, len_cmd);
	ft_fprintf(2, "\033[34mcmd = %s\033[0m\n", ret);
	*i += len_cmd;
	return (ret);
}

char	*get_speop(char *line, int *i)
{
	char	*ret;

	ret = ft_substr(line, 0, 2);
	*i += 2;
	return (ret);
}

char	*get_op(char *line, int *i)
{
	char	*ret;

	ret = our_malloc(sizeof(char)  * 2);
	ret[0] = *line;
	ret[1] = '\0';
	*i += 1;
	return (ret);
}

bool	ft_is_sep(char c)
{
	static const char	whitespace[] = " \t\r\n\v";
	int					i;

	i = -1;
	while (whitespace[++i])
	{
		if (c == whitespace[i])
			return (true);
	}
	return (false);
}

bool	ft_is_op(char c)
{
	static const char	symbols[] = "|<>()&";
	int		i;

	i = -1;
	while (symbols[++i])
		if (c == symbols[i])
			return (true);
	return (false);
}
