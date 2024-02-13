/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuck_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:46:46 by loris             #+#    #+#             */
/*   Updated: 2024/02/13 10:42:42 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token_list(char **tk_list, int tk_count);

// array for the left side of the tree is done
// to do -> Conciliate array and the recursive parsing
// 			Make the array for the right side
//			Conciliate the right side array with the recusrive parsing

void    del_item_array(char **array, char *str_to_delete, int op_place)
{
	int len;
	int	i;

	i = 0;
	len = ft_strlen(str_to_delete);
	while (*array && i < op_place)
	{
		if (ft_strncmp(*array, str_to_delete, len) == 0)
		{
			if (!*(array + 1))
				*array = NULL;
			else
			{
				while (*(array + 1)  && i < op_place)
				{
					*array = *(array + 1);
					array++;
					if (!*(array + 1))
						*array = NULL;
				}
			}
		}
		array++;
	}
}

char    **add_back_array(char **array, char *str)
{
	int len;
	char    **new_array;

	len = ft_tablen(array);
	new_array = our_malloc(sizeof(char*) * (len + 2));
	while (*array)
	{
		*new_array = *array;
		array++;
		new_array++;
	}
	*new_array = str;
	new_array++;
	*new_array = NULL;
	return(new_array - (len + 1));
}

char	*custom_join(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;
	int		len_s1;

	j = 0;
	i = 0;
	if (!s1)
		len_s1 = 0;
	else
		len_s1 = ft_strlen(s1);
	ret = our_malloc((len_s1 + ft_strlen(s2) + 2) *  sizeof(char));
	if (s1)
	{
		while (s1[i])
		{
			ret[i] = s1[i];
			i++;
		}
		ret[i++] = ' ';
	}
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}

/*
	Copy the whole token list until the operator,
	skip the operator and join the next token with the previous one
	Thus if the command args are after the operator, we still have them
*/
char    **new_list_token_redir(char **token_list, int op_place)
{
	char	**split_cmd;
	char	**array;
	int		i;

	// print_token_list(token_list, ft_tablen(token_list));
	ft_fprintf(2,"\033[94mop_place= %d\033[0m\n", op_place);
	split_cmd = NULL;
	array = ft_calloc((op_place + 2) , sizeof(char *));
	i = 0;
	while (i < op_place && token_list[i])
	{
		array[i] = token_list[i];
		i++;
	}
	if (i)
		i--;
	if (token_list[op_place] && token_list[op_place + 1])
		split_cmd = ft_split(token_list[op_place + 1], ' ');
	else
	{
		ft_fprintf(2, "%s: syntax error near unexpected token `newline'", SHELL_NAME);
		dontdoit(2);
		return (NULL);
	}
	if (split_cmd)
		ft_fprintf(2, "\033[94msplit_cmd[0]: %s\nsplit_cmd[1]: %s\033[0m", split_cmd[0], split_cmd[1]);
	if (ft_tablen(split_cmd) == 2 && scan_token((token_list + op_place + 1))->token_type != TK_OP)
		ft_replace_str(&array[i], custom_join(array[i], split_cmd[1]));// frees the old one, it's cleaner
	return (array);
}