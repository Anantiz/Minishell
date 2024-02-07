/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_each_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:42:11 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/07 11:20:05 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int find_operator_addor(char **token_list, int num_token)
{
	int i;

	i = -1;
	while(++i < num_token)
		if (!ft_strncmp(token_list[i], "||", 2) || !ft_strncmp(token_list[i], "&&", 2))
			return (i);
	return (-1);
}
int find_redir_in(char **token_list, int num_token)
{
	int i;

	i = -1;
	while(++i < num_token)
		if (!ft_strncmp(token_list[i], "<", 1) || !ft_strncmp(token_list[i], "<<", 2))
			return (i);
	return (-1);
}

int find_pipeline(char **token_list, int num_token)
{
	int i;

	i = -1;
	while(++i < num_token)
		if (!ft_strncmp(token_list[i], "|", 1))
			return (i);
	return (-1);
}

int find_redir_out(char **token_list, int num_token)
{
	int i;

	i = -1;
	while(++i < num_token)
		if (!ft_strncmp(token_list[i], ">", 1) || !ft_strncmp(token_list[i], ">>", 2))
			return (i);
	return (-1);
}