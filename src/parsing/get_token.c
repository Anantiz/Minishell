/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:26:52 by loris             #+#    #+#             */
/*   Updated: 2024/01/17 10:52:36 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>

bool	ft_is_sep(char c)
{
	char	whitespace[] = " \t\r\n\v";
	int		i;

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
	char	symbols[] = "|<>()'\";&$";
	int		i;

	i = -1;
	while (symbols[++i])
	{
		if (c == symbols[i])
			return (true);
	}
	return (false);
}

int	ft_countword(char *line)
{

	int		count;
	int		i;
    bool    already_cmd;

	i = -1;
	count = 0;
	while (ft_is_sep(*line))
		line++;
	while (line[++i])
	{
		if (ft_is_op(line[i]) == true)
        {
			count++;
            if (line[i] == '|' || line[i] == '&')
                if (line[i+1] == '|' || line[i+1] == '&')
                    i++;
            already_cmd = false;
        }
        if ((!ft_is_op(line[i]) && !ft_is_sep(line[i]) && already_cmd == false))
        {
        	count++;
            already_cmd = true;
        }
	}
	return(count);
}

int	ft_cmdlen(char	*cmd)
{
	int		i;

	i = 0;
	while (ft_is_op(cmd[i]) == false && cmd[i])
		i++;
    i--;
    while (ft_is_sep(cmd[i]) == true)
        i--;
	return (i + 1);
}

char    **ft_strtok(char *line)
{
	char	**list_token;
	int		i;
	int		len_cmd;
	int		j;

	j = 0;
	i = 0;
	list_token = our_malloc(sizeof(char *) * (ft_countword(line) + 1));
	list_token[ft_countword(line)] = NULL;
	while (i < ft_strlen(line))
	{

		if (ft_is_sep(line[i]) == false && ft_is_op(line[i]) == false)
		{
			len_cmd = ft_cmdlen(&line[i]);
			list_token[j++] = ft_substr(line, i, ft_cmdlen(&line[i]));
			i = i + ft_cmdlen(&line[i]);
		}
        else if (ft_is_op(line[i]) == true)
        {
            if (line[i] == '|' || line[i] == '&')
            {
                if (line[i + 1] == '|' || line[i + 1] == '&')
                    list_token[j++]  = ft_substr(line, i, 2);
                    i += 2;
            }
            else
            {
                list_token[j] = our_malloc(sizeof(char)  * 2);
                list_token[j][0] = line[i++];
                list_token[j][1] = '\0';
                j++;
            }
        }
		else
			i++;

	}
	return (list_token);
}

