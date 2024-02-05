/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:08:31 by aurban            #+#    #+#             */
/*   Updated: 2024/02/05 17:46:31 by aurban           ###   ########.fr       */
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
static t_pair_char	**get_appropriate_data(char **args)
{
	t_pair_char	**ret;
	t_pair_char	*pair;
	int			i;
	int			j;

	ret = our_malloc(sizeof(t_pair_char *) * (ft_tablen(args) + 1));
	i = 0;
	j = 0;
	while (args[i])
	{
		pair = create_var_pair(args[i++], NULL);
		if (pair)
			ret[j++] = pair;
	}
	ret[j] = NULL;
	return (ret);
}

static void	free_appropriate_data(t_pair_char **pairs)
{
	int	i;

	i = 0;
	while (pairs[i])
		pair_mfree((void *)(pairs[i++]));
	our_free(pairs);
}

static void	our_export_with_args(t_shell_data *shell_data, t_s_token *token)
{
	int			i;
	t_env		*var;
	t_pair_char	**pairs;

	pairs = get_appropriate_data(token->data.cmd.args);
	i = -1;
	while (pairs[++i])
	{
		if (!pairs[i]->val)
			continue ;
		var = our_get_env(shell_data, pairs[i]->key);
		if (!var)
			var = t_env_add_back(&shell_data->envp, \
				t_env_new_node(ft_strdup(pairs[i]->key), \
				ft_strdup(pairs[i]->val)));
		else
		{
			our_free(var->val);
			var->val = ft_strdup(pairs[i]->val);
		}
	}
	free_appropriate_data(pairs);
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
	t_env		*var;

	if (token->data.cmd.args[1] == NULL || \
	ft_is_blank_str(token->data.cmd.args[1]))
	{
		var = shell_data->envp;
		while (var)
		{
			// Redo this later, sort strings by KEYY, case insensitive
			if (!var->hidden)
			{
				ft_fprintf(STDOUT_FILENO, "declare -x %s=", var->key);
				if (var->val)
					ft_fprintf(STDOUT_FILENO, "%s\n", var->val);
				else
					write(STDOUT_FILENO, "\n", 1);
			}
			var = var->next;
		}
	}
	else
		our_export_with_args(shell_data, token);
	return (SUCCESS);
}
