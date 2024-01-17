/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:10:59 by loris             #+#    #+#             */
/*   Updated: 2024/01/17 11:11:20 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_line(t_shell_data *shell_data, char *line)
{
	(void)shell_data;
	(void)line;
	return (0);
}

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

// void    parse_E()
// {
    
// }
// void    parse_cmd()
// {

// }

// void    parser(char  **token_list)
// {

// }