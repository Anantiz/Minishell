/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:36:06 by aurban            #+#    #+#             */
/*   Updated: 2024/01/21 14:59:14 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// REQUIRED for signal.h
# define _POSIX_C_SOURCE 199309L
# include <signal.h>
extern int		our_g_sig;

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>


# include "libft.h"
# include "pair.h"
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

# define PIPE_ERROR_MSG_INIT "Pipe init error"
# define CMD_ERROR_EXEC_MSG "Command execution error"
# define CMD_ERROR_NOT_FOUND_MSG "Command not found"

/* MISC */

void		display_error(int error);
int			print_shell_intro(t_shell_data *shell_data, t_s_token *node);

/* SESSION */

void		register_signals(void);
int			session_start(t_shell_data *shell_data);
int			parse_line(t_shell_data *shell_data, char *line);
int			execute_commands(t_shell_data *shell_data);

/* SHELL_DATA */

void		cleanup_shell_data(t_shell_data *shell_data);
void		init_shell_data(t_shell_data *shell_data, char **envp);
void		del_tree(t_shell_data *shell_data);

/* PARSING */

int			ft_countword(char *line);
char		**ft_strtok(char *line);

/* PARSING UTILS */

bool		ft_is_sep(char c);
bool		ft_is_op(char c);
int			ft_cmdlen(char	*cmd);
char		*get_cmd(char *line, int *i);
char		*get_speop(char *line, int *i);
char		*get_op(char *line, int *i);

/* EXECUTION */

int			init_pipes(t_shell_data *shell_data);

int			open_pipes(t_s_token *node);
void		close_all_pipes(t_s_token *root);
int			handle_file_bs(t_s_token *node);

int			execute_command(t_shell_data *shell_data, t_s_token *node);
int			parent_process(t_shell_data *shell_data, \
			t_s_token *redir_node, int pid);
void		child_process(t_shell_data *shell_data, \
			t_s_token *node, t_s_token *redir_node);


/* RED FUNCTIONS */

int			check_builtins(t_shell_data *shell_data, t_s_token *node);

int			our_cd(t_shell_data *shell_data, t_s_token *node);
int			our_pwd(t_shell_data *shell_data, t_s_token *node);
int			our_env(t_shell_data *shell_data, t_s_token *node);
int			our_echo(t_shell_data *shell_data, t_s_token *node);
int			our_exit(t_shell_data *shell_data, t_s_token *node);
int			our_unset(t_shell_data *shell_data, t_s_token *node);
int			our_export(t_shell_data *shell_data, t_s_token *node);

typedef int (*t_our_cmd_ptr)(t_shell_data *, t_s_token *);

/* UTILS */

t_s_token	*get_next_node(t_s_token *node);
int			get_cmd_paths(t_shell_data *shell_data, t_s_token *node);

/* T_ENV */
char		**t_env_to_double_char(t_env *envp);
t_env		*our_get_env(t_shell_data *shell_data, char *key);
void		t_env_del_node(t_env **root, t_env *node_);
void		t_env_del_list(t_env **root);
t_env		*t_env_new_node(char *key, char *value);
t_env		*t_env_add_back(t_env **head_, t_env *node);

#endif