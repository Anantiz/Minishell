/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentotree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/02/07 11:50:10 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*   Every time next_token is called, return the next token
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

	if (*token && ft_is_op(*token[0]) == true)
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
	if (*token && !ft_is_op(*token[0]) && !ft_is_sep(*token[0]))
	{
		TK->token_type = TK_CMD;
		TK->data.cmd.args = ft_split(*token, ' ');
		TK->data.cmd.single = single_quote;
	}
	return (TK);
}

// int	main()
// {
// 	char line[] = "cmd1 < file > file paramcmd1";
// 	char **array;
// 	t_s_token	*head;
// 	array = ft_strtok(line);
// 	array++;
// 	head = parse_expression(array, ft_tablen(array), NULL);
// 	replace_file(head);
// 	printf("%d\n", head->right->token_type);
// }