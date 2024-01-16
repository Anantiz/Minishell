/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:36:06 by aurban            #+#    #+#             */
/*   Updated: 2024/01/16 14:33:34 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# include "libft.h"
# include "data_structures.h"

# define SHELL_NAME "Joseph_Shell"
# define  SHELL_NAME_LEN 8

# define FAILURE 1
# define SUCCESS 0
# define PARSING_ERROR 69
# define EXECTION_ERROR 420

# define PIPE_ERROR 1
# define CMD_ERROR_EXEC 2
# define CMD_ERROR_FORK 3
# define CMD_ERROR_NOT_FOUND 4

# define PIPE_ERROR_MSG_INIT "Pipe init error\n"
# define CMD_ERROR_EXEC_MSG "Command execution error\n"
# define CMD_ERROR_NOT_FOUND_MSG "Command not found"

/* MISC */

void		display_error(int error);
void		print_shell_intro(void);

/* SESSION */

int			session_start(t_shell_data *shell_data);
int			parse_line(t_shell_data *shell_data, char *line);
int			execute_commands(t_shell_data *shell_data);

/* SHELL_DATA */

void		clean_shell_data(t_shell_data *shell_data);
void		init_shell_data(t_shell_data *shell_data, char **envp);
void		add_history(t_shell_data *shell_data, char *line);

/* PARSING */

int     	ft_countword(char *line);
char        **ft_strtok(char *line);

/* EXECUTION */

int			setup_pipes(t_shell_data *shell_data);
int			execute_command(t_shell_data *shell_data, t_s_token *node);

/* RED FUNCTIONS */

int			our_commands(t_shell_data *shell_data, t_s_token *node, \
			t_e_our_commands cmd);
char		*our_get_env(t_shell_data *shell_data, char *key);


/* UTILS */

t_s_token	*get_next_node(t_s_token *node);
int			process_cmd_paths(t_shell_data *shell_data, t_s_token *node);


#endif