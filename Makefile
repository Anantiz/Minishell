# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurban <aurban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 10:14:27 by aurban            #+#    #+#              #
#    Updated: 2024/01/12 11:39:20 by aurban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC:=gcc
INCLUDE_PATH=./includes
CFLAGS:=-Wall -Wextra -I$(INCLUDE_PATH) -g3 -fsanitize=address
RM:=rm -rf

NAME:=minishell
LIBFT=libft.a

LIBFT_PATH:=./libft

###########################################################
###########################################################
###########################################################

SRC=\
	main.c	kgb.c

SRC_UTILS:=\
	utils.c

SRC_EXEC:=\
	read_token.c

UTILS_PATH:=utils
SRC_UTILS:= $(addprefix $(UTILS_PATH)/,$(SRC_UTILS))
SRC+= $(SRC_UTILS)

EXEC_PATH:=exec
SRC_EXEC:= $(addprefix $(EXEC_PATH)/,$(SRC_EXEC))
SRC+= $(SRC_UTILS)

# .c -> .o
SRC_PATH:=./src
SRC:= $(addprefix $(SRC_PATH)/,$(SRC))
SRC_OBJECTS:= $(patsubst %.c,%.o,$(SRC))

###########################################################
###########################################################
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