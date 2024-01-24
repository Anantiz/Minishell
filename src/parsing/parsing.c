/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/24 10:21:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_line(t_shell_data *shell_data, char *line)
{
	(void)line;
/* Test*/
	t_s_token	*tk0 = malloc(sizeof(t_s_token));
	t_s_token	*tk1 = malloc(sizeof(t_s_token));
	t_s_token	*tk2 = malloc(sizeof(t_s_token));
	// t_s_token	*tk3 = malloc(sizeof(t_s_token));


	// shell_data->root = tk0;
	// tk0->token_type = TK_OP;
	// tk0->data.op.type = PIPE;
	// tk0->parent = NULL;
	// tk0->left = tk1;
	// tk0->right = tk2;

	// tk1->token_type = TK_CMD;
	// tk1->data.cmd.args = ft_calloc(sizeof(char *), 10);
	// tk1->data.cmd.args[0] = ft_strdup("cat");
	// tk1->data.cmd.args[1] = ft_strdup("Makefile");
	// tk1->data.cmd.paths = NULL;
	// tk1->parent = tk0;
	// tk1->left = NULL;
	// tk1->right = NULL;

	// tk2->token_type = TK_CMD;
	// tk2->data.cmd.args = ft_calloc(sizeof(char *), 10);
	// tk2->data.cmd.args[0] = ft_strdup("sed");
	// tk2->data.cmd.args[1] = ft_strdup("s/SRC/HAHAHA/g");
	// tk2->data.cmd.paths = NULL;
	// tk2->parent = tk0;
	// tk2->left = NULL;
	// tk2->right = NULL;

//echo "Hey mom! > file"
	shell_data->root = tk0;
	tk0->token_type = TK_OP;
	tk0->data.op.type = REDIR_OUT;
	tk0->parent = NULL;
	tk0->left = tk1;
	tk0->right = tk2;

	tk1->token_type = TK_CMD;
	tk1->data.cmd.args = ft_calloc(sizeof(char *), 10);
	tk1->data.cmd.args[0] = ft_strdup("echo");
	tk1->data.cmd.args[1] = ft_strdup("Hey mom!");
	tk1->data.cmd.paths = NULL;
	tk1->parent = tk0;
	tk1->left = NULL;
	tk1->right = NULL;

	tk2->token_type = TK_FILE;
	tk2->data.file.file_path = ft_strdup("Newfile.txt");
	tk2->left = NULL;
	tk2->right = NULL;
	tk2->parent = tk0;

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
