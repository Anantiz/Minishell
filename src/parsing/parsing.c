/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/02/13 16:48:35 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token_list(char **tk_list, int tk_count)
{
	int	i;

	i = 0;
	ft_fprintf(2, "\033[34mToken list: %d\033[0m\n", tk_count);
	while (i < tk_count)
	{
		ft_fprintf(2, "\033[34mToken %d: %s\033[0m\n", i, tk_list[i]);
		i++;
	}
	write(2, ".\n", 2);
}

int	parse_line(t_shell_data *shell_data, char *line)
{
	char		**token_list;
	t_s_token	*token;

	token_list = ft_strtok(line);
	token_list++;
	if (!pre_parsing(token_list, -1))
	{
		shell_data->root = NULL;
		return (FAILURE);
	}
	token = parse_expression(token_list, ft_tablen(token_list), NULL);
	replace_file(token);
	shell_data->root = token;
	return (SUCCESS);
}
