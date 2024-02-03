/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:35:51 by aurban            #+#    #+#             */
/*   Updated: 2024/02/03 16:34:08 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/types.h>
#include "minishell.h"

//getconf ARG_MAX
#define CONFIG_WILDCAR_MAX 2097152

/*
	Allowed functions:
		opendir, readdir, closedir, stat, lstat, fstat, unlink, getcwd
	It should be enough
*/

/*
	Pattern is a string to match, only '*' is supported
*/
static bool	ft_strmatch_wildcard(const char *str, const char *pattern)
{
	int	i;

	if (!*pattern)
		return (!*str);
	i = 0;
	while (str[i] == *pattern)
		(void)(str[i++] && pattern++);
	if (*pattern++ != '*')
		return (false);
	while (str[i] && str[i] != *pattern)
		i++;
	if ((!str[i] && *pattern) || (str[i] != *pattern))
		return (false);
	return (true);
}

/*
	Get a list of all files in the directory
	Exclude the ones not matching the wildcard pattern or hidden files
	Return the list
*/
static char	**get_wild_args(char *str, int *wa_count)
{
	struct dirent	*entry;
	char			**wild_args;
	DIR				*dir;
	int				i;

	wild_args = (our_malloc(sizeof(char *) * CONFIG_WILDCAR_MAX + 1));
	dir = opendir(".");
	if (!dir)
		return (NULL);
	i = 0;
	while ((entry = readdir(dir)))
	{
		if (ft_strmatch_wildcard(entry->d_name, str))
		{
			wild_args[i] = ft_strdup(entry->d_name);
			*wa_count += 1;
			i++;
		}
	}
	wild_args[i] = NULL;
	closedir(dir);
	return (wild_args);
}

/*
	Malloc a new list of args of the (og_list - 1) + wa_count
	While you are before the wildcard arg, copy the args from
		the original list to the new list
	Once you hit the wildcard arg, add the list of files to the new list
	Continue copying the args from the original list to the new list
*/
static void	replace_wild_args(t_s_token *node, char **wild_args, int skip)
{
	char	**new_args;
	int		full_len;
	int		i_wild;
	int		i_new;
	int		i_og;

	i_new = 0;
	i_og = 0;
	i_wild = 0;
	full_len = (ft_strslen(node->data.cmd.args) - 1 + ft_strslen(wild_args));
	new_args = our_malloc(sizeof(char *) * full_len + 1);
	while (i_og < skip)
		new_args[i_new++] = node->data.cmd.args[i_og];
	our_free(node->data.cmd.args[i_og++]);
	while (wild_args[i_wild])
		new_args[i_new++] = wild_args[i_wild++];
	while (node->data.cmd.args[i_og])
		new_args[i_new++] = node->data.cmd.args[i_og++];
	new_args[i_new] = NULL;
	our_free(node->data.cmd.args);
	our_free(wild_args);
	node->data.cmd.args = new_args;
}

/*
	Expand wildcards in the command

	First:
		-Keep a count of args while iterating
		-In all args look for wildcards
	If wildcard:
		-Get a list of files, match the wildcard pattern
		-Strdup the all of these files
			Count them
	Reallocation of the args
		-While you are before the wildcard arg, copy the args from
			the original list to the new list
		-Once you hit the wildcard arg, add the list of files to the new list
		-Continue copying the args from the original list to the new list
*/
void	expand_wildcard(t_s_token *node)
{
	int		i_og;
	int		wa_count;
	char	**wild_args;

	i_og = 0;
	wa_count = 0;
	while (node->data.cmd.args[i_og + wa_count])
	{
		if (ft_strchr(node->data.cmd.args[i_og], '*'))
		{
			wild_args = get_wild_args(node->data.cmd.args[i_og], &wa_count);
			replace_wild_args(node, wild_args, i_og);
			our_free(wild_args);
		}
		i_og++;
	}
}
