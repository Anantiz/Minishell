/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:46:14 by loris             #+#    #+#             */
/*   Updated: 2024/02/13 10:36:29 by aurban           ###   ########.fr       */
=======
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:46:14 by loris             #+#    #+#             */
/*   Updated: 2024/02/13 10:43:19 by lkary-po         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cmd_arg(char **token_list)
{
	int		i;
	char	**arg;
	char	**cmd;
	char	**after_redir;

	after_redir = ft_split(*(token_list + 1), ' ');
	cmd = ft_split(*(token_list - 1), ' ');
	after_redir++;
	i = ft_tablen(after_redir) + ft_tablen(cmd);
	arg = our_malloc(sizeof(char *) * (i + 1));
	arg[i] = NULL;
	while (*cmd)
	{
		*arg = *cmd;
		arg++;
		cmd++;
	}
	while (*after_redir)
	{
		*arg = *after_redir;
		arg++;
		after_redir++;
	}
	return (arg - i);
}

t_s_token	*node_cmd_redir(char **token_list)
{
	t_s_token	*node;
	char		**arg;

	node = our_malloc(sizeof(t_s_token));
	arg = cmd_arg(token_list);
	node->token_type = TK_CMD;
	node->data.cmd.args = arg;
	return (node);
}
