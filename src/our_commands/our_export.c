/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:08:31 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 17:38:11 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
oooooooooo.
`888'   `Y8b
 888      888  .ooooo.  ooo. .oo.    .ooooo.
 888      888 d88' `88b `888P"Y88b  d88' `88b
 888      888 888   888  888   888  888ooo888
 888     d88' 888   888  888   888  888    .o
o888bood8P'   `Y8bod8P' o888o o888o `Y8bod8P'
*/

/*
	We need to split the args into pairs of key/value
	We use the '=' as a separator
*/
static t_pair_char	**get_appropriate_data(char **args, char sep)
{
	t_pair_char	**ret;
	int			i;
	int			j;

	ret = our_malloc(sizeof(t_pair_char *) * (ft_tablen(args) + 1));
	i = 0;
	j = 0;
	while (args[i])
	{
		ret[j] = pair_char_strtok(args[i], sep);
		if (ret[j]->key)
			j++;
		i++;
	}
	ret[j] = NULL;
	return (ret);
}

static void	free_appropriate_data(t_pair_char **pairs)
{
	int i;

	i = 0;
	while (pairs[i])
		pair_char_free(pairs[i++]);
	our_free(pairs);
}

/*
	Syntax: export [name[=value] ...]

	IF value is not set : ignore

	Else :
		- If name does not exist in envp : add it
		- Else : replace it

	For each pair, we check if the key exists in envp
	We update or add it, only if the value is non NULL
*/
int	our_export(t_shell_data *shell_data, t_s_token *token)
{
	t_pair_char	**pairs;
	t_env		*var;
	int			i;

	pairs = get_appropriate_data(token->data.cmd.args, '=');
	i = -1;
	while (pairs[++i])
	{
		if (!pairs[i]->val)
			continue;
		var = our_get_env(shell_data, pairs[i]->key);
		if (!var)
			var = t_env_add_back(&shell_data->envp, t_env_new_node\
				(pairs[i]->key, pairs[i]->val));
		else
		{
			our_free(var->val);
			var->val = ft_strdup(pairs[i]->val);
		}
	}
	free_appropriate_data(pairs);
	return (SUCCESS);
}
