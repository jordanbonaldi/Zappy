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

CXXFLAGS += -lIrrlicht

NAME = zappy_graphic

SRCS =		src/main.cpp            \
            src/Socket.cpp          \
            src/Bot.cpp             \
            src/Data.cpp            \
            src/Commands.cpp        \
            src/Utils.cpp           \
            src/Tile.cpp            \
            src/Resource.cpp        \
            src/ResourceManager.cpp \
            src/Map.cpp             \
            src/Egg.cpp             \
            src/Core.cpp            \
            src/Window.cpp          \
            src/Scene.cpp           \
            src/Event.cpp           \
            src/EventManager.cpp    \
            src/HUD.cpp             \

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o ../$(NAME) $(CXXFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
