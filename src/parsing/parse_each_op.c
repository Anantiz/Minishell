/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_each_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:43:37 by lkary-po          #+#    #+#             */
/*   Updated: 2024/01/22 12:46:48 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_s_token   *parse_expression(char **token_list, int num_token)
{
	int         op_place;
	t_s_token   *node;

	op_place = find_operator_addor(token_list, num_token);
	if (op_place != -1)
	{
		printf("operator place (%d) -> ", op_place);
		printf("\"%s\"\n", token_list[op_place]);
	}
	if (op_place == -1)
	{
		node = parse_pipeline(token_list, num_token);
		return (node);
	}
	node = scan_token((token_list + op_place));
	node->left = parse_expression(token_list, op_place);
	node->right = parse_expression(token_list + op_place + 1, num_token - op_place - 1);
	return (node);
}

t_s_token   *parse_redir(char **token_list, int num_token)
{
	int         op_place;
	t_s_token   *node;

	op_place = find_redir(token_list, num_token);
	if (op_place == -1)
	{
		node = parse_cmd(token_list, num_token);
		return (node);
	}
	node = scan_token((token_list + op_place));
	node->left = parse_expression(token_list, op_place);
	node->right = parse_expression(token_list + op_place + 1, num_token - op_place - 1);
	return (node);
}

t_s_token   *parse_pipeline(char **token_list, int num_token)
{
	int         op_place;
	t_s_token   *node;

	op_place = find_pipeline(token_list, num_token);
	if (op_place == -1)
	{
		node = parse_redir(token_list, num_token);
		return (node);
	}
	node = scan_token((token_list + op_place));
	node->left = parse_expression(token_list, op_place);
	node->right = parse_expression(token_list + op_place + 1, num_token - op_place - 1);
	return (node);
}

t_s_token   *parse_cmd(char **token_list, int num_token)
{
	int         op_place;
	t_s_token   *node;

	node = scan_token(token_list);
	return (node);
}
