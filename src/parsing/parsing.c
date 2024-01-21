/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/21 20:41:16 by aurban           ###   ########.fr       */
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
		fprintf(stderr, "Node is NULL\n");
	else
	{
		fprintf(stderr, "Node %p: type: %s", node, ret_str_tk(node->token_type));
		if (node->token_type == TK_OP)
		{
			fprintf(stderr, "\top: %s, pipe[0]=%d, pipe[1]=%d", \
			ret_str_op_type(node->data.op.type), \
			node->data.op.pipefd[0], node->data.op.pipefd[1]);
		}
	}
	fprintf(stderr, "\n");
}

void	print_node_lite(t_s_token *node)
{
	if (!node)
		fprintf(stderr, "Node is NULL\n");
	else
	{
		fprintf(stderr, "Node %p: type: %s", node, ret_str_tk(node->token_type));
		if (node->token_type == TK_OP)
			fprintf(stderr, "\top: %s", ret_str_op_type(node->data.op.type));
	}
	fprintf(stderr, "\n");
}

int	parse_line(t_shell_data *shell_data, char *line)
{
	(void)line;
/* Test*/
	t_s_token	*tk1 = malloc(sizeof(t_s_token));
	t_s_token	*tk2 = malloc(sizeof(t_s_token));
	t_s_token	*tk3 = malloc(sizeof(t_s_token));

//echo "Hey mom!" > new_file
	tk1->token_type = TK_OP;
	tk1->data.op.type = REDIR_OUT;

	tk2->token_type = TK_CMD;
	tk2->data.cmd.args = malloc(sizeof(char *) * 3);
	tk2->data.cmd.args[0] = ft_strdup("echo");
	tk2->data.cmd.args[1] = ft_strdup("Hey mom!");
	tk2->data.cmd.args[2] = NULL;
	tk2->data.cmd.paths = NULL;

	// tk3->token_type = TK_OP;
	// tk3->data.op.type = REDIR_OUT;

	tk3->token_type = TK_FILE;
	tk3->data.file.file_path = ft_strdup("new_file.txt");

	shell_data->root = tk1;
	tk1->parent = NULL;

	tk1->left = tk2;
	tk1->left->parent = tk1;

	tk1->right = tk3;
	tk1->right->parent = tk1;

	tk3->left = NULL;
	tk3->right = NULL;

	tk2->left = NULL;
	tk2->right = NULL;

	fprintf(stderr, "TREE:\n");
	t_s_token *node = shell_data->root;
	while (node)
	{
		print_node_lite(node);
		node = get_next_node(node);
	}
	fprintf(stderr, "\n");
	return (SUCCESS);
}
