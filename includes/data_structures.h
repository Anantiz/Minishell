/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:24:01 by aurban            #+#    #+#             */
/*   Updated: 2024/01/09 11:41:37 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

# include <stddef.h>

/* ################################ */
/* 				ENUM 				*/
/* ################################ */

typedef enum e_our_commands
{
	CD,
	PWD,
	ECHO,
	UNSET,
	EXPORT,
}t_e_our_commands;

typedef enum e_token_type
{
	FILE,
	CMD,
	OP,
	VAR,
}t_e_token_type;

typedef enum t_e_op_type
{
	PIPE,
	SEMICOLON,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}t_e_op_type;

/* ################################ */
/* 				TOKENS 				*/
/* ################################ */

typedef struct s_file
{
	char	*file_path;
}t_s_file;

typedef struct s_cmd
{
	char	**args;
}t_s_cmd;

typedef struct s_op
{
	t_e_op_type	op_type;
}t_s_op;

// To search in ENVP
typedef struct s_var
{
	char	*var_name;
}t_s_var;

/* ############################## */

union u_token
{
	t_s_file	file;
	t_s_cmd		cmd;
	t_s_op		op;
	t_s_var		var;
};

/* SHITTY */
/* Binary tree */
typedef struct s_token
{
	/* SHITTY */ t_e_token_type	token_type;
	/* SHITTY */ union u_token	data;

	struct s_token	*parent;
	struct s_token	*right;
	struct s_token	*left;
}t_s_token;

/* ################################ */
/* 			Main struct 			*/
/* ################################ */

typedef struct s_shell_data
{
	char		**envp;
}t_shell_data;

#endif