/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentotree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/30 10:11:32 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	parse_line(t_shell_data *shell_data, char *line)
// {
// 	(void)shell_data;
// 	(void)line;
// 	return (0);
// }

/*
*   Every time next_token is call, return the next token
*   until we reach the end of the list of token then return NULL
*   Usefull to take a decision that depend on the next token
*/
char **next_token(char **token_list)
{
	char **n_tok;

	if (token_list + 1)
	{
		n_tok = (token_list + 1);
	}
	else
		return (NULL);
	return (n_tok);
}
/*
*   main test for the next_token function
*/
// int main()
// {
//     char *line = "ls -l || wc -l";
//     int i;
//     char **tok;

//     tok = ft_strtok(line);
//     i = 0;
//     while (*tok)
//     {
//         tok = next_token(tok);

//         printf("(%s)", *tok);
//         i++;
//     }
//     free(tok - i);
// }

/*
*   Take a token from list of token, scan if it is op / cmd / ..
*   and create the appropriate node of the tree. This node will next be
*   used to creat the tree
*/
t_s_token   *scan_token(char **token)
{
	t_s_token   *TK;
	bool		single_quote;

	single_quote = false;
	if (ft_strchr(*token, '\'') != NULL)
		single_quote = true;

	TK = our_malloc(sizeof(t_s_token));

	if (ft_is_op(*token[0]) == true)
	{

		if (ft_strlen(*token) == 2)
		{
			if (*token[0] == '|' && token[0][1] == '|')
			{
				TK->token_type = TK_OP;
				TK->data.op.type = T_OR;

			}
			else if (**(token) == '&' && token[0][1] == '&')
			{
				TK->token_type = TK_OP;
				TK->data.op.type = T_AND;
			}
		}
		else if (**(token) == '|')
		{
			TK->token_type = TK_OP;
			TK->data.op.type = PIPE;
		}
		else if (**(token) == '<')
		{
			TK->token_type = TK_OP;
			TK->data.op.type = REDIR_IN;
		}
		else if (**(token) == '>')
		{
			TK->token_type = TK_OP;
			TK->data.op.type = REDIR_OUT;
		}
		else if (**(token) == '>' && **(token + 1) == '>')
		{
			TK->token_type = TK_OP;
			TK->data.op.type = REDIR_APPEND;
		}
		else if (**(token) == '<' && **(token + 1) == '<')
		{
			TK->token_type = TK_OP;
			TK->data.op.type = REDIR_HEREDOC;
		}
		else if (**(token) == ';')
		{
			TK->token_type = TK_OP;
			TK->data.op.type = SEMICOLON;
		}
	}
	if (!ft_is_op(*token[0]) && !ft_is_sep(*token[0]))
	{
		TK->token_type = TK_CMD;
		TK->data.cmd.args = ft_split(*token, ' ');
		TK->data.cmd.single = single_quote;
	}
	return (TK);
}


// t_s_token   *tree_builder(char **token, int num_token)
// {

// }

/*
*   recursive parsing descent
*   function (expression / redir_out / ..., for the priorities)
*/

t_s_token	*get_next_node(t_s_token *node)
{
	t_s_token	*parent;

	if (!node)
		return (NULL);
	if (node->left)
		return (node->left);
	if (node->right)
		return (node->right);
	while (node->parent)
	{
		parent = node->parent;
		if (parent->right && parent->right != node)
			return (parent->right);
		node = parent;
	}
	return (NULL);
}
// cat < input.txt > output && cat < output | sed s/SRC/HAHAHA/g
// a droite d' une redire c'est tjrs un fichier redir in
// refaire les prioritees sur les redir
// if ARG=VALUE do not parse but add the variable to a linked list : use t_env

// < a une priorite superieur a >
int main()
{
	char *array[] = {"cat", "<", "Makefile", ">", "input.t", "&&", "cat", "<", "input.t", "|", "sed", "s/SRC/HAHAHA/g", NULL};

	char    	**token_list;
	t_s_token   *token;

	token_list = array;

	token = parse_expression(token_list, ft_tablen(token_list), NULL);
	ft_fprintf(2, "TREE:\n");
	t_s_token *node = token;
	int i = 0;
	while (node)
	{
		ft_printf("%d ", i++);
		print_node_lite(node);
		node = get_next_node(node);
	}
	ft_fprintf(2, "\n\n");
}