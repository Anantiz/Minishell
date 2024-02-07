/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_each_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:43:37 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/07 11:49:52 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_s_token   *parse_expression(char **token_list, int num_token, t_s_token *parent_node)
{
	int         op_place;
	t_s_token   *node;

	op_place = find_operator_addor(token_list, num_token);
	// if (op_place != -1)
	// {
	// 	printf("operator place (%d) -> ", op_place);
	// 	printf("\"%s\"\n", token_list[op_place]);
	// }
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

t_s_token   *parse_pipeline(char **token_list, int num_token, t_s_token *parent_node)
{
	int         op_place;
	t_s_token   *node;

	op_place = find_pipeline(token_list, num_token);
	if (op_place == -1)
	{
		node = parse_redir_out(token_list, num_token, parent_node);
		return (node);
	}
	node = scan_token((token_list + op_place));
	node->parent = parent_node;
	node->left = parse_expression(token_list, op_place, node);
	node->right = parse_expression(token_list + op_place + 1, num_token - op_place - 1, node);
	return (node);
}

t_s_token	*parse_redir_out(char **token_list, int num_token, t_s_token *parent_node)
{
	int         op_place;
	t_s_token   *node;
	char		**new_token_left;
	int			i;

	i = 0;

	op_place = find_redir_out(token_list, num_token);
	if (op_place == -1)
	{
		node = parse_redir_in(token_list, num_token, parent_node);
		return (node);
	}
	new_token_left = new_list_token_redir(token_list, op_place);
	node = scan_token((token_list + op_place));
	node->parent = parent_node;
	node->left = parse_expression(new_token_left, ft_tablen(new_token_left), node);
	node->right = parse_expression(token_list + op_place + 1, num_token - op_place - 1, node);
	return (node);
}

t_s_token	*parse_redir_in(char **token_list, int num_token, t_s_token *parent_node)
{
	int         op_place;
	t_s_token   *node;
	char		**new_token_left;
	int			i;

	i = 0;
	op_place = find_redir_in(token_list, num_token);
	if (op_place == -1)
	{
		node = parse_cmd(token_list, num_token, parent_node);
		return (node);
	}
	new_token_left = new_list_token_redir(token_list, op_place);
	node = scan_token((token_list + op_place));
	node->parent = parent_node;
	node->left = parse_expression(new_token_left, ft_tablen(new_token_left), node);
	node->right = parse_expression(token_list + op_place + 1, num_token - op_place - 1, node);
	return (node);
}

t_s_token   *parse_cmd(char **token_list, int num_token, t_s_token *parent_node)
{
	// int         op_place;
	(void)num_token;
	t_s_token   *node;

	node = scan_token(token_list);
	node->parent = parent_node;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

// t_s_token	*redir_node_cmd_behind(char **token_list, int num_token, t_s_token *parent_node)
// {
// 	t_s_token	*node;

// 	node = scan_token(token_list);
// 	node->right = scan_token(token_list + 1);
// 	node->left = node_cmd_redir(token_list);
// 	node->parent = parent_node;
// 	return (node);
// }



// t_s_token	*redir_node_cmd_after(char **token_list, int num_token, t_s_token *parent_node)
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






