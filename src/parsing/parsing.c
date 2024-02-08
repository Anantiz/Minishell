/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/02/08 10:58:14 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token_list(char **tk_list, int tk_count)
{
	int i;

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
	char		**array;
	char		**token_list;
	t_s_token	*token;

	array = ft_strtok(line);
	token_list = array;
	token_list++;
	print_token_list(token_list, ft_tablen(token_list));
	token = parse_expression(token_list, ft_tablen(token_list), NULL);
	replace_file(token);
	shell_data->root = token;
	ft_fprintf(2, "TREE:\n");
	t_s_token *node = token;
	int i = 0;
	while (node)
	{
		ft_printf("%d ", i++);
		print_node_lite(node);
		node = get_next_node(node);
	}
	ft_fprintf(2, "\n\n");
	return (SUCCESS);
}

