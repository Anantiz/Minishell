/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokentotree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:27:27 by loris             #+#    #+#             */
/*   Updated: 2024/01/19 18:45:50 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_line(t_shell_data *shell_data, char *line)
{
	(void)shell_data;
	(void)line;
	return (0);
}

/*
*   Every time next_token is call, return the next token
*   until we reach the end of the list of token then return NULL
*   Usefull to take a decision that depend on the next token
*/
char *next_token(char **token_list)
{
    char *n_tok;

    if (token_list + 1)
        n_tok = *(token_list + 1);
    else
        return (NULL);
    return (n_tok);
}

// int main()
// {
//     char *line = "ls -l || wc -l";
//     int i;
//     char **tok;

//     tok = ft_strtok(line);

//     i = 0;
//     while (*tok)
//     {
//         printf("(%s)", next_token(tok));
//         tok++;
//         i++;
//     }
// }

/*
*   Take a token from list of token, scan if it is op / cmd / ..
*   and create the appropriate node of the tree. This node will next be
*   used to creat the tree
*/
t_s_token   scan_token(char **token)
{
    if (ft_is_op(*token[0]) == true)
    {
        if (*token[0] == '(')
            // do subtree
            ;
        if (*(token) == "|" && *(token + 1) == "|")
            ;
            // or condition
        if (*(token) == "&" && *(token + 1) == "&")
            ;
            // and condition
    }
    if (!ft_is_op(*token[0]) && !ft_is_sep(*token[0]))
    {
        ;
        //  cmd condition
    }
}



void    parse_E()
{

}
// void    parse_cmd()
// {

// }

// void    parser(char  **token_list)
// {

// }
