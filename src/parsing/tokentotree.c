/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentotree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/24 10:08:24 by aurban           ###   ########.fr       */
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

    TK = our_malloc(sizeof(t_s_token));

    if (ft_is_op(*token[0]) == true)
    {
        if (ft_strlen(*token) == 2)
        {
            if (*token[0] == '|' && *token[0 + 1] == '|')
            {
                TK->token_type = TK_OP;
                TK->data.op.type = T_OR;
            }
            else if (**(token) == '&' && **(token + 1) == '&')
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
    if (!ft_is_op(*token[0]) && !ft_is_sep(*token[0])) // Fais attention si token est NULL
    {
        TK->token_type = TK_CMD;
        TK->data.cmd.args = ft_split(*token, ' ');
    }
    return (TK);
}


// /*
// *   recursive parsing descent
// *   function (expression / redir_out / ..., for the priorities)
// */

// int main()
// {
//     char *array[] = {"cat", "|", "echo"};

//     char    **token_list;
//     t_s_token   *token;

//     token_list = array;

//     token = parse_expression(token_list, 2);
//     printf("%d\n", token->token_type);
// }
