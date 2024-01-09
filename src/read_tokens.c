/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:22:44 by aurban            #+#    #+#             */
/*   Updated: 2024/01/09 10:29:33 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	our_command_cd(t_s_token *token)
{
	(void)token;
}

static void	read_token(t_s_token *token)
{
	if (token->token_type == CMD)
	{
		if (ft_strcmp(token->data.cmd.args[0] , "cd"))
		{
			our_command_cd(token);
		}
	}

}

void	read_list(t_s_token *list)
{
	while (list)
	{
		read_token(list);
		list = list->next;
	}
}
