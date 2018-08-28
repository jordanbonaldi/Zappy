##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC = g++

RM = rm -f

UNAME := $(shell uname)

CXXFLAGS += -Iinclude/ -I../ai/include/
CXXFLAGS += -W -Wextra -Wall -Werror -std=c++17 -g3

ifeq ($(UNAME), Darwin)
CXXFLAGS += -I../../../Qt/5.9.6/clang_64/lib/QtWidgets.framework/Headers -I../../../Qt/5.9.6/clang_64/lib/QtGui.framework/Headers -I../../../Qt/5.9.6/clang_64/lib/QtCore.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.13.sdk/System/Library/Frameworks/OpenGL.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.13.sdk/System/Library/Frameworks/AGL.framework/Headers -I../../../Qt/5.9.6/clang_64/mkspecs/macx-clang -F/Users/b_coudoulet/Qt/5.9.6/clang_64/lib
LIBS	 += -framework QtWidgets
LIBS	 += -framework QtGui
LIBS	 += -framework QtCore
LIBS	 += -framework CoreFoundation
LIBS	 += -framework IOKit
endif

ifeq ($(UNAME), Linux)
CXXFLAGS += -I$(HOME)/Qt/5.9.6/gcc_64/include/ -I$(HOME)/Qt/5.9.6/gcc_64/include/QtWidgets -I$(HOME)/Qt/5.9.6/gcc_64/include/QtGui -I$(HOME)/Qt/5.9.6/gcc_64/include/QtCore -I. -isystem /usr/include/libdrm -fPIC
LIBS += -L$(HOME)/Qt/5.9.6/gcc_64/lib -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread
endif
NAME =		../zappy_controller

SRCS =		src/main.cpp \
			src/Controller.cpp \
			../ai/src/Player.cpp \
			../ai/src/CommunicationHelper.cpp \
			../ai/src/Inventory.cpp \
			../ai/src/Utils.cpp \
			../ai/src/Message.cpp \
			../ai/src/SocketClient.cpp

OBJS =		$(SRCS:.cpp=.o)

all: moc $(NAME)

moc:
	moc include/Controller.hpp -o include/Controller.moc

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	$(RM) $(OBJS) include/*.moc

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
