/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:36:06 by aurban            #+#    #+#             */
/*   Updated: 2024/01/30 10:28:37 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>

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

# define SHELL_NAME "\033[31mJoseph_shell:\033[0m"

# define FAILURE -1
# define SUCCESS 0
# define PARSING_ERROR 69
# define EXECTION_ERROR 420

# define PIPE_ERROR 1
# define CMD_ERROR_EXEC 2
# define CMD_ERROR_FORK 3
# define CMD_ERROR_NOT_FOUND 4

// Magic value to differentiate between command errors and not found
# define NOT_IN_BUILTINS 6666666

// Most error messages are hardcoded so it's kinda stupid to have these here
// But not the others
# define PIPE_ERROR_MSG_INIT "Pipe init error"
# define CMD_ERROR_EXEC_MSG "Command execution error"
# define CMD_ERROR_NOT_FOUND_MSG "Command not found"

# define OG_FUCKING_PATH "/usr/local/sbin:/usr/local/bin:\
/usr/sbin:/usr/bin:/sbin:/bin"

extern int	g_our_sig;
typedef int	(*t_our_cmd_ptr)(t_shell_data *, t_s_token *);

/* MISC */

void		print_node(t_s_token *node);
void		print_node_lite(t_s_token *node);
void		display_error(t_shell_data *shell_data, int error);
void		replace_signals(void);
void		our_sig_handl(int sig);
int			print_shell_intro(t_shell_data *shell_data, t_s_token *node);

/* SESSION */

void		register_signals(void);
int			restore_std_streams(t_shell_data *shell_data);
int			session_start(t_shell_data *shell_data);
int			parse_line(t_shell_data *shell_data, char *line);
int			exec_tree(t_shell_data *shell_data);

/* SHELL_DATA */

void		cleanup_shell_data(t_shell_data *shell_data);
void		init_shell_data(t_shell_data *shell_data, char **envp);
void		del_tree(t_shell_data *shell_data);

/* PARSING */

int			ft_countword(char *line);
char		**ft_strtok(char *line);
t_s_token   *scan_token(char **token);

/* PARSING FIND_OP / PARSE_OP */

int 		find_operator_addor(char **token_list, int num_token);
int 		find_redir(char **token_list, int num_token);
int 		find_pipeline(char **token_list, int num_token);
t_s_token   *parse_expression(char **token_list, int num_token, t_s_token *parent_node);
t_s_token   *parse_redir(char **token_list, int num_token, t_s_token *parent_node);
t_s_token   *parse_pipeline(char **token_list, int num_token, t_s_token *parent_node);
t_s_token   *parse_cmd(char **token_list, int num_token, t_s_token *parent_node);

/* PARSING UTILS */

bool		ft_is_sep(char c);
bool		ft_is_op(char c);
int			ft_cmdlen(char	*cmd);
char		*get_cmd(char *line, int *i);
char		*get_speop(char *line, int *i);
char		*get_op(char *line, int *i);
t_s_token	*parse_expression(char **token_list, int num_token, t_s_token *parent_node);
bool    	add_var(char *str);	

/* EXECUTION */

int			init_pipes(t_shell_data *shell_data);

void		find_redir_nodes(t_s_token *cmd_node);
void		assign_redir_nodes(t_s_token *cmd_node, t_s_token *redir_nodes[2]);

int			open_pipes(t_s_token *node);
int			handle_file_bs(t_s_token *node);
void		close_all_pipes(t_s_token *root);
int			cmd_redir_streams(t_s_token *cmd_node);

int			exec_one_command(t_shell_data *shell_data, t_s_token *node);

int			parent_process(t_shell_data *shell_data, \
	t_s_token *cmd_node, int pid);
int			check_builtins(t_shell_data *shell_data, t_s_token *cmd_node);
void		child_process(t_shell_data *shell_data,	t_s_token *cmd_node);

/* RED FUNCTIONS */

int			our_cd(t_shell_data *shell_data, t_s_token *node);
int			our_pwd(t_shell_data *shell_data, t_s_token *node);
int			our_env(t_shell_data *shell_data, t_s_token *node);
int			our_echo(t_shell_data *shell_data, t_s_token *node);
int			our_exit(t_shell_data *shell_data, t_s_token *node);
int			our_unset(t_shell_data *shell_data, t_s_token *node);
int			our_export(t_shell_data *shell_data, t_s_token *node);

/* UTILS */

t_s_token	*get_next_node(t_s_token *node);
t_s_token	*get_next_subtree(t_s_token *node);
int			get_cmd_paths(t_shell_data *shell_data, t_s_token *node);

/* T_ENV */
char		**t_env_to_double_char(t_shell_data *shell_data, t_env *envp);
t_env		*our_get_env(t_shell_data *shell_data, char *key);
void		t_env_del_node(t_env **root, t_env *node_);
void		t_env_del_list(t_env **root);
t_env		*t_env_new_node(char *key, char *value);
t_env		*t_env_add_back(t_env **head_, t_env *node);

#endif