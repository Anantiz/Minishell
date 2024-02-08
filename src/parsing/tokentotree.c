/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentotree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/02/08 10:16:06 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	scan_tk_str_op(char *token_str, t_s_token *node)
{
	// to fix for |||
	node->token_type = TK_OP;
	if (ft_strlen(token_str) == 2)
	{
		if (*token_str == '|' && token_str[1] == '|')
			node->data.op.type = T_OR;
		else if (*token_str == '&' && token_str[1] == '&')
			node->data.op.type = T_AND;
		else if (*token_str == '>' && token_str[1] == '>')
			node->data.op.type = REDIR_APPEND;
		else if (*token_str == '<' && token_str[1] == '<')
			node->data.op.type = REDIR_HEREDOC;
	}
	else if (*token_str == '|')
		node->data.op.type = PIPE;
	else if (*token_str == '<')
		node->data.op.type = REDIR_IN;
	else if (*token_str == '>')
		node->data.op.type = REDIR_OUT;
	else if (*token_str == ';')
		node->data.op.type = SEMICOLON;
}

void	scan_token_extended(char *token_str, t_s_token *token, \
t_e_token_type type)
{
	if (type == TK_CMD)
		scan_tk_str_cmd(token_str, token);
	else if (type == TK_FILE)
		scan_tk_str_file(token_str, token);
	else if (type == TK_OP)
		scan_tk_str_op(token_str, token);
}

/*
*   Take a token from list of token, scan if it is op / cmd / ..
*   and create the appropriate node of the tree. This node will next be
*   used to create the tree
*/
t_s_token   *scan_token(char **token_strs)
{
	t_s_token   *node;

	if (!token_strs || !*token_strs)
		return (NULL);
	node = our_malloc(sizeof(t_s_token));
	if (ft_is_op(**token_strs) == true)
		scan_token_extended(*token_strs, node, TK_OP);
	else if (!ft_is_op(**token_strs) && !ft_is_sep(**token_strs))
		scan_token_extended(*token_strs, node, TK_CMD);
	else
	{
		// To remove in the future
		ft_fprintf(2, "Error: unknown token: \n", *token_strs);
		for (int i = 0; token_strs[i]; i++)
		{
			ft_fprintf(2, "token_strs[%d] = %s\n", i, token_strs[i]);
		}
		return (our_free(node), NULL);
	}
	return (node);
}
