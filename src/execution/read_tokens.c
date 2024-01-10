/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:22:44 by aurban            #+#    #+#             */
/*   Updated: 2024/01/10 10:44:07 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	our_command_cd(t_e_our_commands cmd_name, t_s_token *token)
{
	(void)token;
}

/*antione*/
static void	read_token(t_s_token *token)
{
	if (token->token_type == CMD)
	{
		if (ft_strcmp(token->data.cmd.args[0] , "cd"))
			our_commands(CD, token);
		else if (ft_strcmp(token->data.cmd.args[0] , "pwd"))
			our_commands(ECHO, token);
		else if (ft_strcmp(token->data.cmd.args[0] , "echo"))
			our_commands(EXPORT, token);
		else if (ft_strcmp(token->data.cmd.args[0] , "unset"))
			our_commands(PWD, token);
		else if (ft_strcmp(token->data.cmd.args[0] , "export"))
			our_commands(UNSET, token);
		else
		{
			/* Execute from path */
		}
	}
}

/*loris*/
void	read_list(t_s_token *node)
{
	while (node)
	{
		if (has_siblings(node))
		{
			// Do siblings
		}
		else if (has_children(node))
		{
			// Do child
		}
		else
		{
			// End of Command line
		}

	}
}