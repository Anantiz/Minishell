/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:26:52 by loris             #+#    #+#             */
/*   Updated: 2024/02/08 11:50:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_speop(char *sub_str)
{
	if(!ft_strncmp(sub_str, "||", 2))
		return (true);
	else if (!ft_strncmp(sub_str, "&&", 2))
		return (true);
	else if (!ft_strncmp(sub_str, "<<", 2))
		return (true);
	else if (!ft_strncmp(sub_str, ">>", 2))
		return (true);
	return (false);
}

/*
*	Create a list of token base on the input line
*	every command with his params will be a node of the tree
*	for example :
*		-> (wc -l) | ls -l
*		list_token[0] = "("
*		list_token[1] = "wc -l"
*		list_token[2] = ")"
*		list_token[3] = "|"
*		list_token[4] = "ls -l"
*		list_token[5] = (null)
*
*	Quotes and parenthesis are interpreted as token -> I deal with this when i build the tree
*	(in file tokentotree.c)
*/
int	ft_count_token(char *line)
{
	int		count;
	int		i;
	bool	is_cmd;

	i = -1;
	count = 0;
	is_cmd = false;
	while (ft_is_sep(*line))
		line++;
	while (line[++i])
	{
		if (ft_is_op(line[i]) == true)
		{
			count++;
			if (is_speop(&line[i]) == true)
				i++;
			is_cmd = false;
		}
		else if (is_cmd == false && ft_is_sep(line[i]) == false)
		{
			is_cmd = true;
			count++;
		}
	}
	return(count);
}

/*
*	Split the line into a list of token
*	operators are token
*	parenthesis are
*	cmd and theire params are one token
*	return the list of token (char **)
*/
char    **ft_strtok(char *line)
{
	char	**list_token;
	int		tk_count;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len = (int)ft_strlen(line);
	tk_count = ft_count_token(line);
	ft_fprintf(2, "\033[34mtoken_count = %d\033[0m\n", tk_count);
	list_token = our_malloc(sizeof(char *) * (tk_count + 2));
	list_token[j++] = NULL;
	while (i < len)
	{
        if (is_speop(&line[i]) == true)
			list_token[j++] = get_speop(&line[i], &i);
        else if (ft_is_op(line[i]) == true)
            list_token[j++] = get_op(&line[i], &i);
		else if (ft_is_sep(line[i]) == false)
			list_token[j++] = get_cmd(&line[i], &i);
		i++;
	}
	list_token[j] = NULL;
	return (list_token);
}

// IF exit with ctrl + D
//bash: warning: here-document at line 1 delimited by end-of-file (wanted `EOF')