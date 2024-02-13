/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:44:55 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 16:42:51 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CREATEVARABORT -1
#define CREATEVARGETNAME 15
#define CREATEVARGETCNT 16

/*
	Strdup without quotes, first pass the string in
	`iter_str_check_quote'
	i = strlen of the string
*/
char	*our_strdup_quote(char *str, int i)
{
	char	*temp_str;
	int		j;

	j = 0;
	temp_str = str;
	while (*temp_str)
	{
		if (*temp_str++ != -1)
			j++;
	}
	temp_str = our_malloc((j + 1) * sizeof(char));
	j = 0;
	while (*str && j < i)
	{
		if (*str != -1)
			temp_str[j++] = *str;
		str++;
	}
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
		return (CREATEVARGETCNT);
	}
	else
	{
		j = 0;
		while (forbidden[j])
		{
			if (start[i] == forbidden[j++])
			{
				ft_fprintf(2, "%s `%c': not a valid identifier\n", \
					SHELL_NAME, start[i]);
				return (CREATEVARABORT);
			}
		}
	}
	return (CREATEVARGETNAME);
}

/*
	Transforms syntatic quotes into -1, then you can use
	`our_strdup_quote' to strdup a new string without
	the quotes (don't use any quotes related function after this one)
Params:
	Give the pointer to the char (so it can put it tpo -1)
	Give the pointer to the quote (so it can change it)
Return:
	1 if you should break the string in 2 (closed quote + space or smthg else)
	0 otherwise
*/
int	iter_str_check_quote(char *c, char *quote)
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
	while (start[i])
	{
		if (iter_str_check_quote(&start[i], &quote))
			break ;
		i++;
	}
	if (quote)
	{
		our_free(ret->key);
		ft_fprintf(2, "%s: unexpected EOF while looking for matching "\
		"`%c'\n", SHELL_NAME, quote);
		return (CREATEVARABORT);
	}
	ret->val = our_strdup_quote(start, i);
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
	phase = CREATEVARGETNAME;
	i = 0;
	while ((start[i] && phase != CREATEVARABORT) || phase == CREATEVARGETCNT)
	{
		if (phase == CREATEVARGETNAME)
			phase = create_var_get_name(start, i, ret, name_len);
		else if (phase == CREATEVARGETCNT)
		{
			phase = create_var_get_val(ft_strdup(start + i), ret);
			break ;
		}
		i++;
	}
	if (phase == CREATEVARABORT || phase == CREATEVARGETNAME)
	{
		if (name_len)
			*name_len = -1;
		return (our_free(ret), NULL);
	}
	return (ret);
}
