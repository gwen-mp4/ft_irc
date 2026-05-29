# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: storck <storck@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/29 11:43:10 by gwen              #+#    #+#              #
#    Updated: 2026/05/29 11:51:03 by storck           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = c++
RM = rm -rf
FLAGS = -Wall -Werror -Wextra -g -std=c++98

SRC_DIR = src/
SRC = main.c \
	Client.cpp \
	Server.cpp \
	Channel.cpp

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@echo "ircserv compiled."
	@$(CC) $(FLAGS) $(INC) $(OBJS) -o $(NAME)

clean:
	@echo "Cleaned."
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Full cleaned."
	@$(RM) $(NAME)

re: fclean all

.PHONY: fclean all clean re
