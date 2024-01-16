/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:24:00 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 11:40:35 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Adds an empty path in front of the paths list to get absolute path */
static char	**custom_ft_split(const char *str, char sep)
{
	char	**ret;
	char	**temp;
	int		i;

	temp = ft_split(str, sep);
	ret = our_malloc(sizeof(char *) * (ft_strslen(temp) + 2));
	ret[0] = ft_strdup(".");
	if (temp)
	{
		i = 0;
		while (temp[i])
		{
			ret[i + 1] = temp[i];
			i++;
		}
		free(temp);
		ret[i] = NULL;
	}
	else
		ret[1] = NULL;
	return (ret);
}

// Very inneficient code but does the job fine
/*
	Put any possible path into the node->data.cmd.paths
*/
int	process_cmd_paths(char **envp, t_s_token *node)
{
	char	*old;
	char	*path;
	char	**paths;
	int		i;

	path = our_get_env("PATH");
	paths = custom_ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		old = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(old);
		old = paths[i];
		paths[i] = ft_strjoin(paths[i], node->data.cmd.args[0]);
		free(old);
		i++;
	}
	node->data.cmd.paths = paths;
	return (SUCCESS);
}
