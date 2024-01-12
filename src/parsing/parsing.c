/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/12 14:51:25 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_countword(char *line)
{

}

char    **ft_strtok(char *line)
{
	char	**list_token;

	list_token = safe_malloc(sizeof(char *) * ft_countword(line));
}

int	parse_line(t_shell_data *shell_data, char *line)
{
	(void)shell_data;
	(void)line;
	return (0);
}