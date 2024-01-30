# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurban <aurban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 10:14:27 by aurban            #+#    #+#              #
#    Updated: 2024/01/29 11:49:22 by aurban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC:=gcc
INCLUDE_PATH=./includes
CFLAGS:=-Wall -Wextra -I$(INCLUDE_PATH) -g3 -lreadline -D DEBUG
RM:=rm -rf

NAME=minishell
LIBFT=libft.a

LIBFT_PATH:=./libft

###############################################################################
###############################################################################
###############################################################################

SRC=\
	main.c	session_loop.c signals/sig_handlers.c

SRC_UTILS=\
	utils.c	init_shell_data.c	tree_traversal.c	process_cmd_paths.c		\
	kgb.c	envp_linked_list.c	pair_char.c			other_envp_things.c		\
	print_node.c

SRC_PARSE=\
	parsing.c	get_token.c		parsing.c	tokentotree.c	parsing_utils.c	\

SRC_EXEC=\
	exec.c	data_flow/mario_world.c	exec_command.c	exec_child_process.c	\
	data_flow/redirections_1.c	data_flow/mario_file_bs.c	exec_builtins.c	\
	exec_parent.c	data_flow/redirections_2.c

SRC_ERR=\
	session_error.c

SRC_OURS=\
	our_cd.c		our_pwd.c		our_env.c	our_echo.c	our_exit.c	\
	our_unset.c		our_export.c

UTILS_PATH=utils
SRC_UTILS:= $(addprefix $(UTILS_PATH)/,$(SRC_UTILS))
SRC+= $(SRC_UTILS)

PARSE_PATH=parsing
SRC_PARSE:= $(addprefix $(PARSE_PATH)/,$(SRC_PARSE))
SRC+= $(SRC_PARSE)

EXEC_PATH=execution
SRC_EXEC:= $(addprefix $(EXEC_PATH)/,$(SRC_EXEC))
SRC+= $(SRC_EXEC)

ERR_PATH=error_handlers
SRC_ERR:= $(addprefix $(ERR_PATH)/,$(SRC_ERR))
SRC+= $(SRC_ERR)

OURS_PATH=our_commands
SRC_OURS:= $(addprefix $(OURS_PATH)/,$(SRC_OURS))
SRC+= $(SRC_OURS)

###############################################################################
SRC_PATH=./src
SRC:= $(addprefix $(SRC_PATH)/,$(SRC))
SRC_OBJECTS= $(patsubst %.c,%.o,$(SRC))
###############################################################################

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(SRC_OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $^ -L$(LIBFT_PATH) -lft $(CFLAGS) -o $@

clean:
	@make -C $(LIBFT_PATH)/ clean
	@$(RM) $(SRC_OBJECTS)

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@$(RM) $(NAME) $(LIBFT) checker

re: fclean all

.PHONY: all clean fclean re