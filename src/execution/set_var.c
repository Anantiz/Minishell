/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:44:55 by aurban            #+#    #+#             */
/*   Updated: 2024/02/05 11:24:51 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CREATE_VAR_ABORT -1
#define CREATE_VAR_GET_NAME 15
#define CREATE_VAR_GET_CONTENT 16

static char	*our_awesomest_substr(char *str, int i)
{
	char	*temp_str;
	int		j;

	ft_fprintf(2, "our_awesomest_substr: %s\n", str);
	j = 0;
	temp_str = str;
	while (*temp_str)
	{
		if (*temp_str++ != -1)
			j++;
	}
	temp_str = our_malloc((j + 1 ) * sizeof(char));
	j = 0;
	ft_fprintf(2, "i= %d, our_awesomest_substr: ", i);
	while (*str && j < i)
	{
		ft_fprintf(2, "%c ", *str);
		if (*str != -1)
			temp_str[j++] = *str;
		str++;
	}
	ft_fprintf(2, "\n");
	temp_str[j] = '\0';
	return (temp_str);
}

/*
	Get name, if there is no '=' or '$'
*/
static int	create_var_get_name(const char *start, int i, t_pair_char *ret, \
	int *name_len)
{
	static const char	forbidden[] = "\'\" \t\n\r\v\f\\/;|<>.,[]{}()$*&@%!#`~";
	int					j;

	if (start[i] == '=')
	{
		if (name_len)
			*name_len = i;
		ret->key = ft_substr(start, 0, i);
		return (CREATE_VAR_GET_CONTENT);
	}
	else
	{
		j = 0;
		while (forbidden[j])
		{
			if (start[i] == forbidden[j++])
			{
				ft_fprintf(2, "%s: `%c': not a valid identifier\n", \
					SHELL_NAME, start[i]);
				return (CREATE_VAR_ABORT);
			}
		}
	}
	return (CREATE_VAR_GET_NAME);
}

/*
	Just splitted because norm
*/
static int	create_var_get_val_2(char *c, char *quote)
{
	if (!(*quote) && ft_isspace(*c))
		return (1);
	else if (*c == '"' || *c == '\'')
	{
		if (*quote == 0)
		{
			*quote = *c;
			*c = -1;
		}
		else if (*c == *quote)
		{
			*quote = 0;
			*c = -1;
		}
	}
	return (0);
}

/*
	Get value, if there is a quote, ignore spaces, and grab opoosite quote
	untill next quote of same kind.
	If unclosed quote, return error
*/
static int	create_var_get_val(char *start, t_pair_char *ret)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	ft_fprintf(2, "create_var_get_val: ");
	while (start[i])
	{
		ft_fprintf(2, "%c ", start[i]);
		if (create_var_get_val_2(&start[i], &quote))
			break ;
		i++;
	}
	ft_fprintf(2, "\n");
	if (quote)
	{
		our_free(ret->key);
		ft_fprintf(2, "%s: unexpected EOF while looking for matching "\
		"`%c'\n", SHELL_NAME, quote);
		return (CREATE_VAR_ABORT);
	}
	ret->val = our_awesomest_substr(start, i);
	return (SUCCESS);
}

/*
	Usage:
		-start is the beginning of the variable name, (after the $ if there is one)
	returns:
		-A pair_char with the variable name and the content
		If name_len not NULL
			-It will be set to the length of the variable name
*/
t_pair_char	*create_var_pair(const char *start, int *name_len)
{
	t_pair_char	*ret;
	int			phase;
	int			i;

	ret = our_malloc(sizeof(t_pair_char));
	phase = CREATE_VAR_GET_NAME;
	i = 0;
	while (start[i] && phase != CREATE_VAR_ABORT)
	{
		if (phase == CREATE_VAR_GET_NAME)
			phase = create_var_get_name(start, i, ret, name_len);
		else if (phase == CREATE_VAR_GET_CONTENT)
		{
			phase = create_var_get_val(ft_strdup(start + i), ret);
			break ;
		}
		i++;
	}
	if (phase == CREATE_VAR_ABORT || phase == CREATE_VAR_GET_NAME)
	{
		if (name_len)
			*name_len = -1;
		return (our_free(ret), NULL);
	}
	return (ret);
}

