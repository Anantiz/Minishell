/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_each_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:43:37 by lkary-po          #+#    #+#             */
/*   Updated: 2024/01/30 10:12:10 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_s_token   *parse_expression(char **token_list, int num_token, t_s_token *parent_node)
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
		node = parse_pipeline(token_list, num_token, parent_node);
		return (node);
	}
	node = scan_token((token_list + op_place));
	node->parent = parent_node;
	node->left = parse_expression(token_list, op_place, node);
	node->right = parse_expression(token_list + op_place + 1, num_token - op_place - 1, node);
	return (node);
}

t_s_token   *parse_redir(char **token_list, int num_token, t_s_token *parent_node)
{
	int         op_place;
	t_s_token   *node;

	op_place = find_redir(token_list, num_token);
	if (op_place == -1)
	{
		node = parse_cmd(token_list, num_token, parent_node);
		return (node);
	}
	node = scan_token((token_list + op_place));
	node->parent = parent_node;
	node->left = parse_expression(token_list, op_place, node);
	node->right = parse_expression(token_list + op_place + 1, num_token - op_place - 1, node);
	return (node);
}

t_s_token   *parse_pipeline(char **token_list, int num_token, t_s_token *parent_node)
{
	int         op_place;
	t_s_token   *node;

	op_place = find_pipeline(token_list, num_token);
	if (op_place == -1)
	{
		node = parse_redir(token_list, num_token, parent_node);
		return (node);
	}
	node = scan_token((token_list + op_place));
	node->parent = parent_node;
	node->left = parse_expression(token_list, op_place, node);
	node->right = parse_expression(token_list + op_place + 1, num_token - op_place - 1, node);
	return (node);
}

t_s_token   *parse_cmd(char **token_list, int num_token, t_s_token *parent_node)
{
	int         op_place;
	t_s_token   *node;

	node = scan_token(token_list);
	node->parent = parent_node;
	node->right = NULL;
	node->left = NULL;
	if (parent_is_redir(node) == true)
	{
		if (is_right_child(node) == true)
			node->token_type = TK_FILE;
	}
	return (node);
}
