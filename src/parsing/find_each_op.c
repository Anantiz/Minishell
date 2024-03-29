/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_each_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:42:11 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/13 10:45:04 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_operator_addor(char **token_list, int token_count)
{
	int	i;
	int	parenthesis_count;

	i = -1;
	parenthesis_count = 0;
	while (++i < token_count && token_list[i])
	{
		if (ft_is_o_parenthesis(token_list[i]))
			parenthesis_count++;
		else if (ft_is_c_parenthesis(token_list[i]))
			parenthesis_count--;
		if (parenthesis_count == 0 && (!ft_strncmp(token_list[i], "||", 2) \
		|| !ft_strncmp(token_list[i], "&&", 2)))
		{
			return (i);
		}
	}
	return (-1);
}

int	find_redir_in(char **token_list, int token_count)
{
	int	i;
	int	parenthesis_count;

	i = -1;
	parenthesis_count = 0;
	while (++i < token_count && token_list[i])
	{
		if (ft_is_o_parenthesis(token_list[i]))
			parenthesis_count++;
		else if (ft_is_c_parenthesis(token_list[i]))
			parenthesis_count--;
		if (parenthesis_count == 0 && (!ft_strncmp(token_list[i], "<", 1) \
			|| !ft_strncmp(token_list[i], "<<", 2)))
			return (i);
	}
	return (-1);
}

int	find_pipe_op(char **token_list, int token_count)
{
	int	i;
	int	parenthesis_count;

	i = -1;
	parenthesis_count = 0;
	while (++i < token_count && token_list[i])
	{
		if (ft_is_o_parenthesis(token_list[i]))
			parenthesis_count++;
		else if (ft_is_c_parenthesis(token_list[i]))
			parenthesis_count--;
		if (parenthesis_count == 0 && !ft_strncmp(token_list[i], "|", 1))
			return (i);
	}
	return (-1);
}

int	find_redir_out(char **token_list, int token_count)
{
	int	i;
	int	parenthesis_count;

	i = -1;
	parenthesis_count = 0;
	while (++i < token_count && token_list[i])
	{
		if (ft_is_o_parenthesis(token_list[i]))
			parenthesis_count++;
		else if (ft_is_c_parenthesis(token_list[i]))
			parenthesis_count--;
		if (parenthesis_count == 0 && (!ft_strncmp(token_list[i], ">", 1) \
		|| !ft_strncmp(token_list[i], ">>", 2)))
			return (i);
	}
	return (-1);
}
