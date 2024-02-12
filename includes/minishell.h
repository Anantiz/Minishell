/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:36:06 by aurban            #+#    #+#             */
/*   Updated: 2024/02/12 18:50:13 by aurban           ###   ########.fr       */
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
# include <sys/types.h>
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
# define PIPE_CLOSED -669

# define PIPE_ERROR 1
# define CMD_ERROR_EXEC 2
# define CMD_ERROR_FORK 3
# define CMD_ERROR_NOT_FOUND 4

// Magic value to differentiate between command errors and not found
// Hopefully it's not a valid errno, so it should be fine
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
void		replace_signals_2(void);
// void		our_sig_handl(int sig);
int			print_shell_intro(t_shell_data *shell_data, t_s_token *node);

/* SESSION */

void		register_signals(void);
int			restore_std_streams(t_shell_data *shell_data);
int			session_start(t_shell_data *shell_data);
int			parse_line(t_shell_data *shell_data, char *line);
int			exec_tree(t_shell_data *shell_data);

/* SHELL_DATA */

void		cleanup_shell_data(t_shell_data *shell_data);
void		init_shell_data(t_shell_data *shell_data, char **envp, \
char *argv[]);
void		del_tree(t_shell_data *shell_data);

/* PARSING */

int			ft_count_token(char *line);
char		**ft_strtok(char *line);
t_s_token	*scan_token(char **token);
void		scan_tk_str_cmd(char *token_str, t_s_token *token);
void		scan_tk_str_file(char *token_str, t_s_token *token);
void		scan_token_extended(char *token_str, t_s_token *token, \
t_e_token_type type);

/* PARSING FIND_OP / PARSE_OP */

int			find_operator_addor(char **token_list, int num_token);
int			find_redir_out(char **token_list, int num_token);
int			find_redir_in(char **token_list, int num_token);
int			find_pipe_op(char **token_list, int num_token);

t_s_token	*parse_expression_clean(char **token_list, int token_count, \
t_s_token *parent_node);
t_s_token	*parse_expression(char **token_list, int num_token, \
t_s_token *parent_node);
t_s_token	*parse_addor(char **token_list, int token_count, \
t_s_token *parent_node);
t_s_token	*parse_redir_in(char **token_list, int num_token, \
t_s_token *parent_node);
t_s_token	*parse_redir_out(char **token_list, int num_token, \
t_s_token *parent_node);
t_s_token	*parse_pipeline(char **token_list, int num_token, \
t_s_token *parent_node);
t_s_token	*parse_cmd(char **token_list, int num_token, \
t_s_token *parent_node);
bool   		ft_is_o_parenthesis(char *token);
bool    	ft_is_c_parenthesis(char *token);
bool		ft_is_parenthesis(char **token_list);
void		del_parenthesis(char **token_list, int op_place);

/* PARSING UTILS */

bool		ft_is_sep(char c);
bool		ft_is_op(char c);
int			ft_cmdlen(char	*cmd);
char		*get_cmd(char *line, int *i);
char		*get_speop(char *line, int *i);
char		*get_op(char *line, int *i);
t_s_token	*parse_expression(char **token_list, int num_token, \
t_s_token *parent_node);
bool		add_var(char *str);
void		replace_file(t_s_token *node);
t_s_token	*new_tokenfile(t_s_token *node);

/* PARSING REDIR */

void    del_item_array(char **array, char *str_to_delete, int op_place);
char    **add_back_array(char **array, char *str);
char	*custom_join(char *s1, char *s2);
char    **new_list_token_redir(char **token_list, int op_place);


/* EXECUTION */

void		expand_wildcard(t_s_token *node);
int			pre_init(t_shell_data *shell_data);
void		our_heredoc(t_s_token *redir_node);
void		find_redir_nodes(t_s_token *cmd_node);
t_s_token	*handle_redir_subtree(t_s_token *node);
int			open_pipes(t_s_token *node);
int			handle_file_bs(t_s_token *node);
void		close_all_pipes(t_s_token *root);
int			cmd_redir_streams(t_s_token *cmd_node);

int			exec_one_command(t_shell_data *shell_data, t_s_token *node);

int			parent_process(t_shell_data *shell_data, \
	t_s_token *cmd_node, int pid);
int			check_builtins(t_shell_data *shell_data, t_s_token *cmd_node);
void		child_process(t_shell_data *shell_data,	t_s_token *cmd_node);
void		parent_close_pipes(t_s_cmd *cmd);

/* Exec utils*/
void		wait_last_subtree(t_shell_data *shell_data);

/* VARIABLES BULLSHIT*/

t_pair_char	*create_var_pair(const char *start, int *name_len);
t_env		*our_get_env(t_shell_data *shell_data, char *key);

/* RED FUNCTIONS */

int			our_cd(t_shell_data *shell_data, t_s_token *node);
int			our_pwd(t_shell_data *shell_data, t_s_token *node);
int			our_env(t_shell_data *shell_data, t_s_token *node);
int			our_echo(t_shell_data *shell_data, t_s_token *node);
int			our_exit(t_shell_data *shell_data, t_s_token *node);
int			our_unset(t_shell_data *shell_data, t_s_token *node);
int			our_export(t_shell_data *shell_data, t_s_token *node);

/* UTILS */

bool		dontdoit(int sate);
bool		isbasicredir(t_s_token *node);
t_s_token	*get_next_node(t_s_token *node);
t_s_token	*get_next_node_no_op(t_s_token *node);
t_s_token	*get_next_logical_op(t_s_token *node);
int			get_cmd_paths(t_shell_data *shell_data, t_s_token *node);

char		*get_clean_path_shell(t_shell_data *shell_data);
char		*get_clean_path(t_shell_data *shell_data, char *str_path);
void		expand_variables(t_shell_data *shell_data, t_s_token *node);
void		init_cmd_token(t_shell_data *shell_data, t_s_token *node);
bool		is_logop(t_s_token *node);

/* T_ENV */
char		**t_env_to_double_char(t_env *envp);
void		t_env_del_node(t_env **root, t_env *node_);
void		t_env_del_list(t_env **root);
t_env		*t_env_new_node(char *key, char *value);
t_env		*t_env_add_back(t_env **head_, t_env *node);

#endif