// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   get_token.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/01/16 08:26:52 by loris             #+#    #+#             */
// /*   Updated: 2024/01/21 16:36:49 by loris            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// /*
// *	Create a list of token base on the input line
// *	every command with his params will be a node of the tree
// *	for example :
// *		-> (wc -l) | ls -l
// *		list_token[0] = "("
// *		list_token[1] = "wc -l"
// *		list_token[2] = ")"
// *		list_token[3] = "|"
// *		list_token[4] = "ls -l"
// *		list_token[5] = (null)
// *
// *	Quotes and parenthesis are interpreted as token -> I deal with this when i build the tree
// *	(in file tokentotree.c)
// */

// int	ft_countword(char *line)
// {
// 	int		count;
// 	int		i;
// 	bool	already_cmd;

// 	i = -1;
// 	count = 0;
// 	while (ft_is_sep(*line))
// 		line++;
// 	while (line[++i])
// 	{
// 		if (ft_is_op(line[i]) == true)
// 		{
// 			count++;
//             if (line[i] == '|' || line[i] == '&')
//                 if (line[i+1] == '|' || line[i+1] == '&')
//                     i++;
//             already_cmd = false;
//         }
//         if ((!ft_is_op(line[i]) && !ft_is_sep(line[i]) && already_cmd == false))
//         {
//         	count++;
//             already_cmd = true;
//         }
// 	}
// 	return(count);
// }

// /*
// *	Split the line into a list of token
// *	operators are token
// *	parenthesis are
// *	cmd and theire params are one token
// *	return the list of token (char **)
// */
// char    **ft_strtok(char *line)
// {
// 	char	**list_token;
// 	int		i;
// 	int		j;
// 	int		word;

// 	j = 0;
// 	i = 0;
// 	word = ft_countword(line);
// 	list_token = our_malloc(sizeof(char *) * (word + 1));
// 	list_token[word] = NULL;
// 	while (i < ft_strlen(line))
// 	{
// 		if (ft_is_sep(line[i]) == false && ft_is_op(line[i]) == false)
// 			list_token[j++] = get_cmd(&line[i], &i);
//         else if (ft_is_op(line[i]) == true)
//         {
//             if ((line[i] == '|' || line[i] == '&') && (line[i + 1] == '|' || line[i + 1] == '&'))
//                 list_token[j++] = get_speop(&line[i], &i);
//             else
//                 list_token[j++] = get_op(&line[i], &i);
//         }
// 		else
// 			i++;
// 	}
// 	return (list_token);
// }

// // int main()
// // {
// //     char *line = "(ls -l) || $ARG | wc -l";
// //     int i;
// //     char **tok;

// //     tok = ft_strtok(line);
// //     tok = ft_strtok(line);

// //     i = 0;
// //     while (tok[i] != NULL)
// //     {
// //         printf("(%s)", tok[i]);
// //         i++;
// //     }
// // 	i = 0;
// // 	while (tok[i])
// //     {
// //         free(tok[i]);
// //         i++;
// //     }
// // 	free(tok);
// // }