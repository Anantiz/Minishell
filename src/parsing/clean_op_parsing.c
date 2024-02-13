/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_op_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:20:13 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 14:08:14 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef t_s_token	*(*t_tk_parsing)(char **, int , t_s_token *);
typedef int			(*t_tk_op_finding)(char **, int);

/*
	Refactoring of the `parse_each_op.c` file because it is super ugly
	and I don't want to work on it.
*/

/*
	We will iterate over a loop of function pointers to find what token
	we are dealing with, if one fails we will go to the next one until
	we find the right one.
	That is much cleaner that the current implementation.
	Where you just return(next_op_parsing())
	Like at what point did you think that was a good idea?
*/
t_s_token	*parse_expression_clean(char **token_list, int token_count, \
t_s_token *parent_node)
{
	static const t_tk_parsing		op_parsing[] = {parse_addor, \
	parse_pipeline, parse_redir_out, parse_redir_in, parse_cmd};
	static const t_tk_op_finding	op_find[] = {find_operator_addor, \
	find_pipe_op, find_redir_out, find_redir_in};
	int								op_place;
	int								i;

	i = 0;
	while (i < 4)
	{
		op_place = op_find[i](token_list, token_count);
		if (op_place > -1)
			break ;
		i++;
	}
	return (op_parsing[i](token_list, token_count, parent_node));
}
