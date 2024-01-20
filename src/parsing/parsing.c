/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/20 15:31:29 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_line(t_shell_data *shell_data, char *line)
{
	(void)line;

/* Test*/
	t_s_token	*tk1 = malloc(sizeof(t_s_token));
	t_s_token	*tk2 = malloc(sizeof(t_s_token));
	t_s_token	*tk3 = malloc(sizeof(t_s_token));
	t_s_token	*tk4 = malloc(sizeof(t_s_token));

/*  do echo "Hey mom!" > new_file*/
	tk1->token_type = TK_OP;
	tk1->data.op.type = PIPE;

	tk2->token_type = TK_CMD;
	tk2->data.cmd.args = malloc(sizeof(char *) * 3);
	tk2->data.cmd.args[0] = ft_strdup("echo");
	tk2->data.cmd.args[1] = ft_strdup("Hey mom!");
	tk2->data.cmd.args[2] = NULL;
	tk2->data.cmd.paths = NULL;

	tk3->token_type = TK_OP;
	tk3->data.op.type = REDIR_OUT;

	tk4->token_type = TK_FILE;
	tk4->data.file.file_path = ft_strdup("new_file");

	shell_data->root = tk1;
	tk1->left = tk2;
	tk1->right = tk3;
	tk3->left = tk4;

	tk1->left->parent = tk1;
	tk1->right->parent = tk1;
	tk3->left->parent = tk3;
	tk1->parent = NULL;
	tk2->left = NULL;
	tk2->right = NULL;
	tk3->right = NULL;
	tk4->left = NULL;
	tk4->right = NULL;
	return (SUCCESS);
}
