/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:36:06 by aurban            #+#    #+#             */
/*   Updated: 2024/01/18 11:52:11 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// REQUIRED for signal.h
# define _POSIX_C_SOURCE 199309L
# include <signal.h>
int		g_sig;

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# include "libft.h"
# include "data_structures.h"

# define SHELL_NAME "Joseph_shell"

# define FAILURE 1
# define SUCCESS 0
# define PARSING_ERROR 69
# define EXECTION_ERROR 420

# define PIPE_ERROR 1
# define CMD_ERROR_EXEC 2
# define CMD_ERROR_FORK 3
# define CMD_ERROR_NOT_FOUND 4

# define NOT_IN_BUILTINS 66

# define PIPE_ERROR_MSG_INIT "Pipe init error\n"
# define CMD_ERROR_EXEC_MSG "Command execution error\n"
# define CMD_ERROR_NOT_FOUND_MSG "Command not found"

/* MISC */

void		display_error(int error);
void		print_shell_intro(t_shell_data *shell_data, t_s_token *node);

/* SESSION */

int			session_start(t_shell_data *shell_data);
int			parse_line(t_shell_data *shell_data, char *line);
int			execute_commands(t_shell_data *shell_data);

/* SHELL_DATA */

void		clean_shell_data(t_shell_data *shell_data);
void		init_shell_data(t_shell_data *shell_data, char **envp);
void		add_history(t_shell_data *shell_data, char *line);

/* PARSING */

int			ft_countword(char *line);
char		**ft_strtok(char *line);

/* EXECUTION */

int			setup_pipes(t_shell_data *shell_data);
int			execute_command(t_shell_data *shell_data, t_s_token *node);

/* RED FUNCTIONS */

int			check_builtins(t_shell_data *shell_data, t_s_token *node);
char		*our_get_env(t_shell_data *shell_data, char *key);

int			our_cd(t_shell_data *shell_data, t_s_token *node);
int			our_pwd(t_shell_data *shell_data, t_s_token *node);
int			our_env(t_shell_data *shell_data, t_s_token *node);
int			our_echo(t_shell_data *shell_data, t_s_token *node);
int			our_exit(t_shell_data *shell_data, t_s_token *node);
int			our_unset(t_shell_data *shell_data, t_s_token *node);
int			our_export(t_shell_data *shell_data, t_s_token *node);

# define OUR_COMMANDS_NAMES {"cd", "pwd", "env", "echo", "exit", "unset", \
		"export", "red_square", NULL};

# define OUR_COMMANDS_FNC_PTR {our_cd, our_pwd, our_env, our_echo, \
		our_exit, our_unset, our_export, print_shell_intro, NULL};

typedef int (*t_our_cmd_ptr)(t_shell_data *, t_s_token *);

/* UTILS */

t_s_token	*get_next_node(t_s_token *node);
int			process_cmd_paths(t_shell_data *shell_data, t_s_token *node);
char		**t_env_to_double_char(t_env *envp);

void		t_env_del_node(t_env *node);
void		t_env_del_list(t_env *list);
t_env		*t_env_new_node(char *key, char *value);
t_env		*t_env_add_back(t_env **head_, t_env *node);

#endif