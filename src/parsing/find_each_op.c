/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_each_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:42:11 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/08 08:16:36 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int find_operator_addor(char **token_list, int token_count)
{
	int i;

	i = -1;
	while(++i < token_count)
		if (!ft_strncmp(token_list[i], "||", 2) \
		|| !ft_strncmp(token_list[i], "&&", 2))
			return (i);
	return (-1);
}
int find_redir_in(char **token_list, int token_count)
{
	int i;

	i = -1;
	while(++i < token_count)
		if (!ft_strncmp(token_list[i], "<", 1) \
		|| !ft_strncmp(token_list[i], "<<", 2))
			return (i);
	return (-1);
}

int find_pipe_op(char **token_list, int token_count)
{
	int i;

	i = -1;
	while(++i < token_count)
		if (!ft_strncmp(token_list[i], "|", 1))
			return (i);
	return (-1);
}

int find_redir_out(char **token_list, int token_count)
{
	int i;

	i = -1;
	while(++i < token_count)
		if (!ft_strncmp(token_list[i], ">", 1) \
		|| !ft_strncmp(token_list[i], ">>", 2))
			return (i);
	return (-1);
}
