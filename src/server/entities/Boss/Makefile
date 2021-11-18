##
## EPITECH PROJECT, 2021
## Mini-Pacman
## File description:
## Makefile
##

SRC			=	Boss.cpp					\
				../../engine/ServerEntity.cpp		\
				../../engine/CustomRect.cpp			\
				../../EntityLoad.cpp				\

CXXFLAGS 	=	-Wall -Wextra -I../../engine -I../../../interface -fPIC
NAME 		= 	Boss.so

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) -shared $(CXXFLAGS)
	rm -f $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all

.PHONY: all clean fclean re
