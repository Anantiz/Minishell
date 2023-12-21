/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:36:06 by aurban            #+#    #+#             */
/*   Updated: 2023/12/21 12:52:03 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

typedef enum e_token_type
{
	FILE,
	CMD,
	OPERATOR,
}t_e_token_type;

typedef union u_token
{
	char	*file_path;
	char	**cmd_args;
}t_u_token;

typedef struct s_token
{
	t_u_token		text_data;
	t_e_token_type	token_type;
	struct s_token	*next;
}t_s_token;

typedef struct s_shell_data
{
	// Shall be initialized at boot then edited when required
	char	**env;


}t_shell_data;


#endif