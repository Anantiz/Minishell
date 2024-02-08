/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recheck_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:30:17 by loris             #+#    #+#             */
/*   Updated: 2024/02/08 09:12:16 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_file(t_s_token *node)
{
	while (node)
	{
		if (node->token_type == TK_OP && (node->data.op.type > PIPE \
			&& node->data.op.type < REDIR_HEREDOC))
			node->right = new_tokenfile(node->right);
		node = get_next_node(node);
	}
}

t_s_token *new_tokenfile(t_s_token *node)
{
	t_s_token	*new_node;

	print_node(node);
	new_node = our_malloc(sizeof(t_s_token));
	scan_tk_str_file(node->data.cmd.args[0], new_node);
	new_node->parent = node->parent;
	new_node->left = node->left;
	new_node->right = node->right;
	ft_fprintf(2, "IM FREEING THIS SHIT\n");
	our_free(node);
	return (new_node);
}
