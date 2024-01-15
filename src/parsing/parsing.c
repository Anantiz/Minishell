/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/15 12:54:14 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>

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

int	ft_cmdlen(char	*cmd)
{
	int		i;

	i = 0;
	while (ft_is_sep(cmd[i]) == false)
		i++;
	return (i);
}

char    **ft_strtok(char *line)
{
	char	**list_token;
	int		i;
	int		len_cmd;

	i = 0;
	list_token = our_malloc(sizeof(char *) * (ft_countword(line) + 1));
	list_token[ft_countword(line)] = NULL;
	while (*line)
	{
		len_cmd = ft_cmdlen(line);
		while (ft_is_sep(*line))
			line++;
		list_token[i++] = ft_substr(line, 0, len_cmd);
		line + len_cmd;
	}
	return (list_token);
}

int	main()
{
	int	i = 0;
	char *line;
	char **token;
	line = "cmd | cmd1 d   ";
	token = ft_strtok(line);
	while (token[i])
	{
		printf("%s\n", token[i++]);
	}
}

// int	parse_line(t_shell_data *shell_data, char *line)
// {
// 	(void)shell_data;
// 	(void)line;
// 	return (0);
// }