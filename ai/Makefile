##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC = g++

RM = rm -f

CXXFLAGS += -Iinclude/
CXXFLAGS += -W -Wextra -Wall -Werror -std=c++17 -g3

NAME = ../zappy_ai

SRCS =		src/main.cpp \
			src/SocketClient.cpp \
			src/CommunicationHelper.cpp \
			src/Inventory.cpp \
			src/Player.cpp \
			src/Utils.cpp \
			src/Message.cpp \

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
