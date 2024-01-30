/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/30 10:19:47 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_line(t_shell_data *shell_data, char *line)
{
	char		 **array;
	char    	**token_list;
	t_s_token   *token;

	array = ft_strtok(line);
	token_list = array;
	token = parse_expression(token_list, ft_tablen(token_list), NULL);
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
