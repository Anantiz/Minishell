/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_perenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:32:02 by loris             #+#    #+#             */
/*   Updated: 2024/02/13 10:35:27 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// to do :  - function to parse recursivly parenthesis after redire / before cmd
//          - function  to create a new array who cut the parenthesis
//          - this array will be the new "left" of the new parenthesis function

bool	ft_is_parenthesis(char **token_list)
{
	if (ft_strncmp(*token_list, "(", 1) == 0)
		return (true);
	return (false);
}

void	del_parenthesis(char **token_list, int op_place)
{
	int	i;

	i = 0;
	token_list[op_place] = NULL;
	while (token_list[i])
	{
		token_list[i] = token_list[i + 1];
		i++;
	}
}
