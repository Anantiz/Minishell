/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:21:54 by aurban            #+#    #+#             */
/*   Updated: 2024/02/05 18:46:52 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ret_str_tk(int e)
{
	if (e == TK_CMD)
		return ("TK_CMD");
	else if (e == TK_OP)
		return ("TK_OP");
	else if (e == TK_FILE)
		return ("TK_FILE");
	else if (e == TK_VAR)
		return ("TK_VAR");
	else
		return ("TK_UNKNOWN");
}

static char	*ret_str_op_type(int e)
{
	if (e == SEMICOLON)
		return ("SEMICOLON");
	else if (e == T_OR)
		return ("T_OR");
	else if (e == T_AND)
		return ("T_AND");
	else if (e == PIPE)
		return ("PIPE");
	else if (e == REDIR_IN)
		return ("REDIR_IN");
	else if (e == REDIR_OUT)
		return ("REDIR_OUT");
	else if (e == REDIR_APPEND)
		return ("REDIR_APPEND");
	else if (e == REDIR_HEREDOC)
		return ("REDIR_HEREDOC");
	else
		return ("OP_UNKNOWN");
}

void	print_node(t_s_token *node)
{
	if (!node)
		ft_fprintf(2, "Node is NULL\n");
	else
	{
		ft_fprintf(2, "Node %p: type: %s", node, ret_str_tk(node->token_type));
		if (node->token_type == TK_OP)
		{
			ft_fprintf(2, "\top: %s, pipe[0]=%d, pipe[1]=%d", \
			ret_str_op_type(node->data.op.type), \
			node->data.op.pipefd[0], node->data.op.pipefd[1]);
		}
	}
	if (node->token_type == TK_CMD)
	{
		ft_fprintf(2, "\targs: ");
		int i = 0;
		while (node->data.cmd.args[i])
		{
			ft_fprintf(2, "%s ", node->data.cmd.args[i]);
			i++;
		}
	}
	ft_fprintf(2, "\n");
}

void	print_node_lite(t_s_token *node)
{
	if (!node)
		ft_fprintf(2, "Node is NULL\n");
	else
	{
		ft_fprintf(2, "Node %p: type: %s", node, ret_str_tk(node->token_type));
		if (node->token_type == TK_OP)
			ft_fprintf(2, "\top: %s", ret_str_op_type(node->data.op.type));
	}
	ft_fprintf(2, "\n");
}
