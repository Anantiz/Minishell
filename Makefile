# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurban <aurban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 10:14:27 by aurban            #+#    #+#              #
#    Updated: 2024/01/09 10:23:21 by aurban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC:=gcc
INCLUDE_PATH=./includes
CFLAGS:=-Wall -Werror -Wextra -I$(INCLUDE_PATH)
RM:=rm -rf

NAME:=minishell
LIBFT=libft.a

SRC_PATH:=./src
LIBFT_PATH:=./libft

SRC_FILES:\
	main.c	read_tokens.c


SRC_FILES:= $(addprefix $(SRC_PATH)/,$(SRC_FILES))
SRC_OBJECTS:= $(patsubst %.c,%.o,$(SRC_FILES))

# SRC_FILES_BONUS:=

# SRC_PATH_BONUS:=$(SRC_PATH)/bonus
# SRC_FILES_BONUS:= $(addprefix $(SRC_PATH_BONUS)/,$(SRC_FILES_BONUS))
# BONUS_OBJ:= $(patsubst %.c,%.o,$(SRC_FILES_BONUS))

all: $(NAME)

$(NAME): $(SRC_OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $^ -L$(LIBFT_PATH) -lft $(CFLAGS) -o $@

# bonus: $(BONUS_OBJ)
# 	@make -C $(LIBFT_PATH)
# 	@$(CC) $^ -L$(LIBFT_PATH) -lft $(CFLAGS)

both: $(NAME) bonus

clean:
	@make -C $(LIBFT_PATH)/ clean
	@$(RM) $(SRC_OBJECTS)

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@$(RM) $(NAME) $(LIBFT) checker

re: fclean all

.PHONY: all clean fclean re libft.a bonus minishell