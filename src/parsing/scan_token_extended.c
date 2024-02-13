/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_token_extended.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:11:01 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 12:03:20 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	strdup_single_q(char **arg, bool *single)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	*single = true;
	while ((*arg)[i])
		iter_str_check_quote((*arg)[i++], &quote);
	ft_replace_str(arg, our_strdup_quote(arg, i));
}

static void	strdup_dbl_q(char **arg, bool *single)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	*single = false;
	while ((*arg)[i])
		iter_str_check_quote((*arg)[i++], &quote);
	ft_replace_str(arg, our_strdup_quote(arg, i));
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
		if (args[i][0] == '\'')
			strdup_single_q(&args[i], &token->data.cmd.single[i]);
		else if (args[i][0] == '\"')
			strdup_dbl_q(&args[i], &token->data.cmd.single[i]);
		else
			token->data.cmd.single[i] = false;
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
	if (*token_str == '\'')
		strdup_single_q(&token->data.file.file_path, &token->data.file.single);
	else if (*token_str == '\"')
		strdup_dbl_q(&token->data.file.file_path, &token->data.file.single);
	else
		token->data.file.single = false;
}
