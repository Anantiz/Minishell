/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/12 15:07:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_countword(char *line)
{

}

char    **ft_strtok(char *line)
{
	char	**list_token;

	list_token =  our_malloc(sizeof(char *) * ft_countword(line));
}

int	parse_line(t_shell_data *shell_data, char *line)
{
	(void)shell_data;
	(void)line;
	return (0);
}