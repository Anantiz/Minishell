/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:51:50 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 18:04:04 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	our_cd(t_shell_data *shell_data, t_s_token *node)
{
	t_env	*var;

	printf("our_cd\n");
	if (chdir(node->data.cmd.args[1]))
	{
		ft_fprintf(2, "cd: %s: %s\n", node->data.cmd.args[1], strerror(errno));
		return (FAILURE);
	}
	var = our_get_env(shell_data, "PWD");
	our_free(var->val);
	var->val = getcwd(NULL, 0);
	if (var->val == NULL)
	{
		ft_fprintf(2, "cd: %s: %s\n", node->data.cmd.args[1], strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}
