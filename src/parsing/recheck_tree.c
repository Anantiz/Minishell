/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recheck_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:30:17 by loris             #+#    #+#             */
/*   Updated: 2024/01/30 12:33:46 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	replace_file(t_s_token *node)
{
	while (node)
	{

		if (node)
		{
			write(1, "d", 1);

				node->right;
		}
		node = get_next_node(node);
	}
}

t_s_token	*new_tokenfile(t_s_token *node)
{
	t_s_token	*TK;

	TK->token_type = TK_FILE;
	TK->data.file.
}