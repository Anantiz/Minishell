/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuck_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:46:46 by loris             #+#    #+#             */
/*   Updated: 2024/02/07 11:20:01 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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
	printf("len = %d\n", len);
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

	j = 0;
	i = 0;
	ret = our_malloc((ft_strlen(s1) + ft_strlen(s2) + 2) *  sizeof(char));
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = ' ';
	i++;
	while (s2[j])
	{
		ret[i] = s2[j];
		j++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char    **new_list_token_redir(char **token_list, int op_place)
{
	char	**array;
	int		i;
	char	**split_cmd;

	i = 0;
	array = our_malloc((op_place + 1) * sizeof(char *));
	array[op_place] = NULL;
	while (array[i] && i < op_place)
	{
		array[i] = token_list[i];
		i++;
	}
	split_cmd = ft_split(*(token_list + op_place + 1), ' ');
	if (ft_tablen(split_cmd) == 2 && scan_token((token_list + op_place + 2))->token_type != TK_OP)
		array[i - 1] = custom_join(array[i - 1], split_cmd[1]);
	return (array);
}



// int main()
// {
//     char *array[] = {NULL};
//     char  **token;
// 	char  **ret_array;
// 	int		i;

// 	i = 0;


//     token = array;

//     ret_array = new_list_token_redir(token, 3);
// 	ret_array = new_list_token_redir(ret_array, 1);
//     while(*ret_array)
//     {
//         printf("%d | %s\n", i, *ret_array);
// 		i++;
//         ret_array++;
//     }
// }