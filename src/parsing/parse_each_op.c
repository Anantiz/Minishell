/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_each_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:43:37 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/08 10:56:24 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*

	Note from not the author:
		-The `find_X` recursive method is ugly.
		-Like just loop through each function and call the appropriate one.
		These High level of depth is mostly copy pasted code.
		-This is a good example of how to not do it. :D

*/

t_s_token   *parse_expression(char **token_list, int token_count, t_s_token *parent_node)
{
	return (parse_expression_clean(token_list, token_count, parent_node));
}

t_s_token	*parse_addor(char **token_list, int token_count, t_s_token *parent_node)
{
	int         op_place;
	t_s_token   *node;

	op_place = find_operator_addor(token_list, token_count);
	node = scan_token((token_list + op_place));
	if (!node)
		return (NULL);
	node->parent = parent_node;
	node->left = parse_expression(token_list, op_place, node);
	node->right = parse_expression(token_list + op_place + 1, token_count - op_place - 1, node);
	return (node);
}

t_s_token   *parse_pipeline(char **token_list, int token_count, t_s_token *parent_node)
{
	int			op_place;
	t_s_token	*node;

	op_place = find_pipe_op(token_list, token_count);
	node = scan_token((token_list + op_place));
	if (!node)
		return (NULL);
	node->parent = parent_node;
	node->left = parse_expression(token_list, op_place, node);
	node->right = parse_expression(token_list + op_place + 1, token_count - op_place - 1, node);
	return (node);
}

t_s_token	*parse_redir_out(char **token_list, int token_count, t_s_token *parent_node)
{
	int         op_place;
	t_s_token   *node;
	char		**new_token_left;

	op_place = find_redir_out(token_list, token_count);
	new_token_left = new_list_token_redir(token_list, op_place);
	node = scan_token((token_list + op_place));
	if (!node)
		return (NULL);
	node->parent = parent_node;
	node->left = parse_expression(new_token_left, ft_tablen(new_token_left), node);
	node->right = parse_expression(token_list + op_place + 1, token_count - op_place - 1, node);
	return (node);
}

t_s_token	*parse_redir_in(char **token_list, int token_count, t_s_token *parent_node)
{
	int         op_place;
	t_s_token   *node;
	char		**new_token_left;

	op_place = find_redir_in(token_list, token_count);
	node = scan_token((token_list + op_place));
	if (!node)
		return (NULL);
	new_token_left = new_list_token_redir(token_list, op_place);
	node->parent = parent_node;
	node->left = parse_expression(new_token_left, ft_tablen(new_token_left), node);
	node->right = parse_expression(token_list + op_place + 1, token_count - op_place - 1, node);
	return (node);
}

t_s_token   *parse_cmd(char **token_list, int token_count, t_s_token *parent_node)
{
	t_s_token   *node;

	(void)token_count;
	ft_fprintf(2, "CMD LOOKING FOR TOKEN: %s\n", *token_list);
	node = scan_token(token_list);
	if (!node)
		return (NULL);
	node->parent = parent_node;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

// t_s_token	*redir_node_cmd_behind(char **token_list, int token_count, t_s_token *parent_node)
// {
// 	t_s_token	*node;

// 	node = scan_token(token_list);
// 	node->right = scan_token(token_list + 1);
// 	node->left = node_cmd_redir(token_list);
// 	node->parent = parent_node;
// 	return (node);
// }



// t_s_token	*redir_node_cmd_after(char **token_list, int token_count, t_s_token *parent_node)
// {
// 	t_s_token	*node;

// 	node = scan_token(token_list);
// 	node->right = scan_token(token_list + 1);
// 	node->left = scan_token(token_list + 2);
// 	return (node);
// }

// bool	is_cmd_behind(char **token_list)
// {
// 	if (*(token_list - 1))
// 		return (true);
// 	return (false);
// }
