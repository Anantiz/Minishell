/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/26 11:48:19 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_line(t_shell_data *shell_data, char *line)
{
	(void)line;
/* Test*/
	t_s_token	*tk0 = our_malloc(sizeof(t_s_token));
	t_s_token	*tk1 = our_malloc(sizeof(t_s_token));
	t_s_token	*tk2 = our_malloc(sizeof(t_s_token));
	t_s_token	*tk3 = our_malloc(sizeof(t_s_token));
	t_s_token	*tk4 = our_malloc(sizeof(t_s_token));
	t_s_token	*tk5 = our_malloc(sizeof(t_s_token));
	t_s_token	*tk6 = our_malloc(sizeof(t_s_token));
	t_s_token	*tk7 = our_malloc(sizeof(t_s_token));
	t_s_token	*tk7_1 = our_malloc(sizeof(t_s_token));
	t_s_token	*tk7_2 = our_malloc(sizeof(t_s_token));
	t_s_token	*tk8 = our_malloc(sizeof(t_s_token));

// cat Makefile | sed s/SRC/HAHAHA/g
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

// echo "Hey mom! > Newfile.txt"
	// shell_data->root = tk0;
	// tk0->token_type = TK_OP;
	// tk0->data.op.type = PIPE;
	// tk0->parent = NULL;
	// tk0->left = tk1;
	// tk0->right = tk2;

	// tk1->token_type = TK_CMD;
	// tk1->data.cmd.args = ft_calloc(sizeof(char *), 10);
	// tk1->data.cmd.args[0] = ft_strdup("echo");
	// tk1->data.cmd.args[1] = ft_strdup("FIRST ECHO");
	// tk1->data.cmd.paths = NULL;
	// tk1->parent = tk0;
	// tk1->left = NULL;
	// tk1->right = NULL;

	// tk2->token_type = TK_OP;
	// tk2->data.op.type = PIPE;
	// tk2->parent = tk0;
	// tk2->left = tk3;
	// tk2->right = tk4;

	// tk3->token_type = TK_CMD;
	// tk3->data.cmd.args = ft_calloc(sizeof(char *), 10);
	// tk3->data.cmd.args[0] = ft_strdup("cat");
	// // tk3->data.cmd.args[1] = ft_strdup("b");
	// tk3->data.cmd.paths = NULL;
	// tk3->parent = tk2;
	// tk3->left = NULL;
	// tk3->right = NULL;

	// tk4->token_type = TK_OP;
	// tk4->data.op.type = PIPE;
	// tk4->parent = tk2;
	// tk4->left = tk5;
	// tk4->right = tk6;

	// tk5->token_type = TK_CMD;
	// tk5->data.cmd.args = ft_calloc(sizeof(char *), 10);
	// tk5->data.cmd.args[0] = ft_strdup("sed");
	// tk5->data.cmd.args[1] = ft_strdup("s/FIRST/LAST/g");
	// tk5->data.cmd.paths = NULL;
	// tk5->parent = tk4;
	// tk5->left = NULL;
	// tk5->right = NULL;

	// tk6->token_type = TK_CMD;
	// tk6->data.cmd.args = ft_calloc(sizeof(char *), 10);
	// tk6->data.cmd.args[0] = ft_strdup("sed");
	// tk6->data.cmd.args[1] = ft_strdup("s/ECHO/CMD/g");
	// tk6->data.cmd.paths = NULL;
	// tk6->parent = tk4;
	// tk6->left = NULL;
	// tk6->right = NULL;

// ls -l
	// shell_data->root = tk0;
	// tk0->token_type = TK_CMD;
	// tk0->data.cmd.args = ft_calloc(sizeof(char *), 10);
	// tk0->data.cmd.args[0] = ft_strdup("ls");
	// tk0->data.cmd.args[1] = ft_strdup("-l");
	// tk0->data.cmd.paths = NULL;
	// tk0->parent = NULL;
	// tk0->left = NULL;
	// tk0->right = NULL;

// cat < input.txt > output && cat < output | sed s/SRC/HAHAHA/g
	shell_data->root = tk0;
	tk0->token_type = TK_OP;
	tk0->data.op.type = REDIR_OUT;
	tk0->parent = NULL;
	tk0->left = tk1;
	tk0->right = tk4;

	tk1->token_type = TK_OP;
	tk1->data.op.type = REDIR_IN;
	tk1->parent = tk0;
	tk1->left = tk2;
	tk1->right = tk3;

	tk2->token_type = TK_CMD;
	tk2->data.cmd.args = ft_calloc(sizeof(char *), 10);
	tk2->data.cmd.args[0] = ft_strdup("cat");
	tk2->data.cmd.paths = NULL;
	tk2->parent = tk1;
	tk2->left = NULL;
	tk2->right = NULL;
	tk2->data.cmd.is_last = false;

	tk3->token_type = TK_FILE;
	tk3->data.file.file_path = ft_strdup("Makefile");
	tk3->left = NULL;
	tk3->right = NULL;
	tk3->parent = tk1;

	tk4->token_type = TK_FILE;
	tk4->data.file.file_path = ft_strdup("some_test_file");
	tk4->left = NULL;
	tk4->right = tk5;
	tk4->parent = tk0;

	tk5->token_type = TK_OP;
	tk5->data.op.type = T_AND;
	tk5->parent = tk4;
	tk5->left = tk6;
	tk5->right = NULL;

	tk6->token_type = TK_OP;
	tk6->data.op.type = PIPE;
	tk6->parent = tk5;
	tk6->left = tk7;
	tk6->right = tk8;

	tk7->token_type = TK_OP;
	tk7->data.op.type = REDIR_IN;
	tk7->parent = tk6;
	tk7->left = tk7_1;
	tk7->right = tk7_2;

	tk7_2->token_type = TK_FILE;
	tk7_2->data.file.file_path = ft_strdup("some_test_file");
	tk7_2->left = NULL;
	tk7_2->right = NULL;
	tk7_2->parent = tk7;

	tk7_1->token_type = TK_CMD;
	tk7_1->data.cmd.args = ft_calloc(sizeof(char *), 10);
	tk7_1->data.cmd.args[0] = ft_strdup("cat");
	tk7_1->data.cmd.paths = NULL;
	tk7_1->parent = tk7;
	tk7_1->left = NULL;
	tk7_1->right = NULL;
	tk7_1->data.cmd.is_last = false;

	tk8->token_type = TK_CMD;
	tk8->data.cmd.args = ft_calloc(sizeof(char *), 10);
	tk8->data.cmd.args[0] = ft_strdup("sed");
	tk8->data.cmd.args[1] = ft_strdup("s/SRC/HAHAHA/g");
	tk8->data.cmd.paths = NULL;
	tk8->parent = tk6;
	tk8->left = NULL;
	tk8->right = NULL;
	tk8->data.cmd.is_last = true;

	ft_fprintf(2, "TREE:\n");
	t_s_token *node = shell_data->root;
	int i = 0;
	while (node)
	{
		ft_printf("%d ", i++);
		print_node_lite(node);
		node = get_next_node(node);
	}
	ft_fprintf(2, "\n\n");
	return (SUCCESS);
}
