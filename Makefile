# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurban <aurban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 10:14:27 by aurban            #+#    #+#              #
#    Updated: 2024/01/12 12:45:56 by aurban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC:=gcc
INCLUDE_PATH=./includes
CFLAGS:=-Wall -Wextra -I$(INCLUDE_PATH) -g3 -fsanitize=address
RM:=rm -rf

NAME=minishell
LIBFT=libft.a

LIBFT_PATH:=./libft

###########################################################
###########################################################
###########################################################

SRC=\
	main.c	session_loop.c

SRC_UTILS=\
	utils.c	kgb.c	init_shell_data.c

SRC_PARSE=\
	parsing.c

SRC_EXEC=\
	execute.c	read_tokens.c

SRC_ERR=\
	session_error.c

SRC_OURS=\
	our_cd.c

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

###########################################################
SRC_PATH=./src
SRC:= $(addprefix $(SRC_PATH)/,$(SRC))
SRC_OBJECTS= $(patsubst %.c,%.o,$(SRC))
###########################################################


all: $(NAME)

$(NAME): $(SRC_OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $^ -L$(LIBFT_PATH) -lft $(CFLAGS) -o $@

both: $(NAME) bonus

clean:
	@make -C $(LIBFT_PATH)/ clean
	@$(RM) $(SRC_OBJECTS)

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@$(RM) $(NAME) $(LIBFT) checker

re: fclean all

.PHONY: all clean fclean re libft.a