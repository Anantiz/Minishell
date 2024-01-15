/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/12 16:12:28 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "stdbool.h"
#include <stdio.h>

bool	ft_is_sep(char c)
{
	// char	symbols[] = "|<>()'\";&$";
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

int	ft_countword(char *line)
{

	int		count;
	int		i;

	i = -1;
	count = 0;
	while (ft_is_sep(*line))
		line++;
	while (line[++i])
	{
		if (ft_is_sep(line[i]) == false && (ft_is_sep(line[i + 1]) == true || line[i + 1] == '\0'))
			count++;
	}
	return(count);
}

char    **ft_strtok(char *line)
{
	char	**list_token;

	list_token =  our_malloc(sizeof(char *) * (ft_countword(line) + 1));
	list_token[ft_countword(line)] = NULL;
	
}

int	parse_line(t_shell_data *shell_data, char *line)
{
	(void)shell_data;
	(void)line;
	return (0);
}