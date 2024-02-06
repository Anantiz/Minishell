/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:24:01 by aurban            #+#    #+#             */
/*   Updated: 2024/02/06 19:06:17 by aurban           ###   ########.fr       */
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
	RED_SQUARE,
	E_END_CMD,
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
	SEMICOLON,
	T_OR,
	T_AND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	E_END_OP,
}t_e_op_type;

/* ################################ */
/* 				TOKENS 				*/
/* ################################ */

/*
	Because s_file and s_comand
	get initalized by the same function
	the redir_nodes has to be at the same place
*/

typedef struct s_file
{
	struct s_token	*redir_nodes[2];
	char			*file_path;
	int				fd;
	bool			single;
}t_s_file;

typedef struct s_cmd
{
	struct s_token	*redir_nodes[2];
	char			**args;
	char			**paths;
	bool			is_last;
	bool			*single;
}t_s_cmd;

typedef struct s_op
{
	t_e_op_type	type;
	int			pipefd[2];
	char		*heredoc_str;
	char		*eof;
	size_t		heredoc_len;
	bool		did_exec;
}t_s_op;

/* ############################## */

// Union of all possible tokens
union u_token
{
	t_s_file	file;
	t_s_cmd		cmd;
	t_s_op		op;
};

/* Binary tree */
typedef struct s_token
{
	t_e_token_type	token_type;
	union u_token	data;
	struct s_token	*parent;
	struct s_token	*right;
	struct s_token	*left;
}t_s_token;

/*
ENVP Linked_list
	Because refactoring would be tedious (like more than 5 min, crazy right ?)
	The struct will stay as is, and I won't use a t_pair_char
*/
typedef struct s_env
{
	bool			hidden;
	char			*key;
	char			*val;
	struct s_env	*next;
}t_env;

/* ################################ */
/* 			Main struct 			*/
/* ################################ */

typedef struct s_shell_data
{
	t_env		*envp;
	t_env		*shell_var;
	t_s_token	*root;
	t_s_cmd		*last_command;
	int			stdin_fd;
	int			stdout_fd;
	char		*our_pwd;
	char		*our_oldpwd;
	int			last_pid;
	int			last_wstatus;
	int			cmd_count;
	int			pid_count;
	int			*pid_list;
	int			skip;
}t_shell_data;

#endif