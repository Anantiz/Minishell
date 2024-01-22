/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentotree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:27:27 by loris             #+#    #+#             */
/*   Updated: 2024/01/22 11:16:21 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
                TK->data.op.op_type = T_OR;
            }
            else if (**(token) == '&' && **(token + 1) == '&')
            {
                TK->token_type = TK_OP;
                TK->data.op.op_type = T_AND;
            }
        }
        else if (**(token) == '|')
        {
            TK->token_type = TK_OP;
            TK->data.op.op_type = PIPE;
        }
        else if (**(token) == '<')
        {
            TK->token_type = TK_OP;
            TK->data.op.op_type = REDIR_IN;
        }
        else if (**(token) == '>')
        {
            TK->token_type = TK_OP;
            TK->data.op.op_type = REDIR_OUT;
        }
        else if (**(token) == '>' && **(token + 1) == '>')
        {
            TK->token_type = TK_OP;
            TK->data.op.op_type = REDIR_APPEND;
        }
        else if (**(token) == '<' && **(token + 1) == '<')
        {
            TK->token_type = TK_OP;
            TK->data.op.op_type = REDIR_HEREDOC;
        }
        else if (**(token) == ';')
        {
            TK->token_type = TK_OP;
            TK->data.op.op_type = SEMICOLON;
        }
    }
    if (!ft_is_op(*token[0]) && !ft_is_sep(*token[0]))
    {
        if (ft_strncmp("echo", *token, 4) == 0)
        {

            TK->token_type = TK_CMD;
            TK->data.cmd.args = ft_split(*token, ' ');
        }
        if (ft_strncmp("pwd", *token, 3) == 0)
        {
            TK->token_type = TK_CMD;
            TK->data.cmd.args = ft_split(*token, ' ');
        }
        if (ft_strncmp("export", *token, 6) == 0)
        {
            TK->token_type = TK_CMD;
            TK->data.cmd.args = ft_split(*token, ' ');
        }
        if (ft_strncmp("unset", *token, 5) == 0)
        {
            TK->token_type = TK_CMD;
            TK->data.cmd.args = ft_split(*token, ' ');
        }
        if (ft_strncmp("env", *token, 3) == 0)
        {
            TK->token_type = TK_CMD;
            TK->data.cmd.args = ft_split(*token, ' ');
        }
        if (ft_strncmp("exit", *token, 4) == 0)
        {
            TK->token_type = TK_CMD;
            TK->data.cmd.args = ft_split(*token, ' ');
        }
    }
    return (TK);
}
int find_operator(char **token_list, int num_token)
{
    int i;

    i = -1;
    while(i < num_token)
        if (!ft_strncmp(token_list[i], "||", 2) || !ft_strncmp(token_list[i], "&&", 2))
            return (i);
    return (-1);
}

/*
*   recursive parsing descent
*   function (expression / redir_out / ..., for the priorities)
*/
t_s_token   *parse_expression(char **token_list, int num_token)
{
    int         op_place;
    t_s_token   *node;

    op_place = find_operator(token_list, num_token);
    if (op_place == -1)
    {
        node = parse_pipeline(token_list, num_token);
        return (node);
    }
    node = scan_token((token + op_place));
    node->left = parse_expression(token_list, op_place);
    node->right = parse_expression(token_list + op_place + 1, num_token - op_place - 1); // second params should be just op_place ? focus on this tomorrow
    return (node);
}



t_s_token   *parse_redir_out(char **token_list, int num_token)
{

}

t_s_token   *parse_redir_in(char **token_list, int num_token)
{

}
t_s_token   *parse_pipeline(char **token_list, int num_token)
{

}

t_s_token

int main()
{
    char *array[] = {"cat", "|", "echo"};

    char    **token_list;
    t_s_token   *token;

    token_list = array;

    token = parse_E(token_list);
    printf("%d\n", token->token_type);
}