# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: storck <storck@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/29 11:43:10 by gwen              #+#    #+#              #
#    Updated: 2026/05/29 16:42:51 by storck           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = c++
RM = rm -rf
FLAGS = -Wall -Werror -Wextra -g -std=c++98

SRC_DIR = src/
SRC = Channel.cpp \
	Client.cpp \
	Server.cpp \
	Command.cpp \
	HandleCommands.cpp \
	Commands/Invite.cpp \
	Commands/Join.cpp \
	Commands/Kick.cpp \
	Commands/Mode.cpp \
	Commands/Nick.cpp \
	Commands/Notice.cpp \
	Commands/Part.cpp \
	Commands/Pass.cpp \
	Commands/PrivMsg.cpp \
	Commands/Quit.cpp \
	Commands/Topic.cpp \
	Commands/User.cpp \
	main.cpp

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR = obj/
OBJ = $(SRC:.cpp=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
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
