/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_init_cmd_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:43:59 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 17:28:49 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmd_token_last(t_s_token *node)
{
	if (node->parent && node->parent->right == node \
		&& !node->right && !node->left)
		node->data.cmd.is_last = true;
	else if ((!node->parent || is_logop(node->parent)) \
		&& !node->right && !node->left)
		node->data.cmd.is_last = true;
	else
		node->data.cmd.is_last = false;
}

void	init_cmd_token(t_shell_data *shell_data, t_s_token *node)
{
	node->data.cmd.redir_nodes[0] = NULL;
	node->data.cmd.redir_nodes[1] = NULL;
	shell_data->cmd_count++;
	init_cmd_token_last(node);
	expand_variables(shell_data, node);
	expand_wildcard(node);
}
