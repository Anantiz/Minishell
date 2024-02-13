/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_token_extended.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:11:01 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 12:32:26 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Has no effect if there is no quotes and no effect on the last odd quote
*/
static void	cmd_strdup_quote(char **arg, bool *single)
{
	int		i;
	int		j;
	char	quote;
	char	*tmp1;
	char	*tmp2;

	quote = 0;
	i = 0;
	tmp1 = ft_strchr(*arg, '\'');
	tmp2 = ft_strchr(*arg, '\"');
	if ((tmp1 && !tmp2) || (tmp1 && tmp2 && tmp1 < tmp2))
		*single = true;
	while ((*arg)[i])
		iter_str_check_quote(&(*arg)[i++], &quote);
	if (quote != 0) // if unclosed, put back the quote where it should be
	{
		j = i - 1;
		while (j > -1 && (*arg)[j] != -1)
			j--;
		if ((*arg)[j] == -1)
			(*arg)[j] = quote;
	}
	ft_replace_str(arg, our_strdup_quote(*arg, i));
}

//Handle quotes in command arguments
void	scan_tk_str_cmd(char *token_str, t_s_token *token)
{
	char	**args;
	int		i;

	token->data.cmd.redir_nodes[0] = NULL;
	token->data.cmd.redir_nodes[1] = NULL;
	token->token_type = TK_CMD;
	args = ft_split(token_str, ' ');
	token->data.cmd.single = our_malloc(ft_strslen(args) * sizeof(bool));
	i = 0;
	while (args[i])
	{
		token->data.cmd.single[i] = false;
		cmd_strdup_quote(&args[i], &token->data.cmd.single[i]);
		i++;
	}
	token->data.cmd.args = args;
}

// Handle quotes in file paths
void	scan_tk_str_file(char *token_str, t_s_token *token)
{
	token->token_type = TK_FILE;
	if (!token_str)
	{
		token->data.file.file_path = ft_strdup("");
		token->data.file.single = false;
		return ;
	}
	token->data.file.file_path = ft_strdup(token_str);
	token->data.file.single = false;
	cmd_strdup_quote(&token->data.file.file_path, &token->data.file.single);
}
