/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/23 11:33:23 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *ret_str_tk(int e)
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

static char *ret_str_op_type(int e)
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

int	parse_line(t_shell_data *shell_data, char *line)
{
	(void)line;
/* Test*/
	t_s_token	*tk0 = malloc(sizeof(t_s_token));
	t_s_token	*tk1 = malloc(sizeof(t_s_token));
	t_s_token	*tk2 = malloc(sizeof(t_s_token));
	// t_s_token	*tk3 = malloc(sizeof(t_s_token));

//echo "Hey mom!" > new_file
	shell_data->root = tk0;

	tk0->token_type = TK_OP;
	tk0->data.op.type = PIPE;
	tk0->parent = NULL;
	tk0->left = tk1;
	tk0->right = tk2;

	tk1->token_type = TK_CMD;
	tk1->data.cmd.args = ft_calloc(sizeof(char *), 10);
	tk1->data.cmd.args[0] = ft_strdup("cat");
	tk1->data.cmd.args[1] = ft_strdup("Makefile");
	tk1->data.cmd.paths = NULL;
	tk1->parent = tk0;
	tk1->left = NULL;
	tk1->right = NULL;

	tk2->token_type = TK_CMD;
	tk2->data.cmd.args = ft_calloc(sizeof(char *), 10);
	tk2->data.cmd.args[0] = ft_strdup("sed");
	tk2->data.cmd.args[1] = ft_strdup("s/SRC/HAHAHA/g");
	tk2->data.cmd.paths = NULL;
	tk2->parent = tk0;
	tk2->left = NULL;
	tk2->right = NULL;

	ft_fprintf(2, "TREE:\n");
	t_s_token *node = shell_data->root;
	while (node)
	{
		print_node_lite(node);
		node = get_next_node(node);
	}
	ft_fprintf(2, "\n\n");
	return (SUCCESS);
}
