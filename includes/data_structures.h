/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:24:01 by aurban            #+#    #+#             */
/*   Updated: 2024/01/18 10:29:22 by aurban           ###   ########.fr       */
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
	ENV,
	ECHO,
	EXIT,
	UNSET,
	EXPORT,
	END_OF_ENUM,
}t_e_our_commands;

typedef enum e_token_type
{
	TK_FILE,
	TK_CMD,
	TK_OP,
	TK_VAR,
}t_e_token_type;

typedef enum t_e_op_type
{
	T_AND,
	T_OR,
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
	char	**paths;
}t_s_cmd;

typedef struct s_op
{
	t_e_op_type	type;
	int			pipefd[2];
}t_s_op;

// To search in shell_data->envp
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
	t_e_token_type	token_type;
	union u_token	data;

	struct s_token	*parent;
	struct s_token	*right;
	struct s_token	*left;
}t_s_token;

/* ############################## */
// ENVP Linked_list
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

/* ################################ */
/* 			Main struct 			*/
/* ################################ */

typedef struct s_shell_data
{
	t_env		*envp;
	t_llstr		*get_line_history;
	t_s_token	*root;
}t_shell_data;

#endif