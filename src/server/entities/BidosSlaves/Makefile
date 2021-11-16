##
## EPITECH PROJECT, 2021
## Mini-Pacman
## File description:
## Makefile
##

SRC			=	BidosSlaves.cpp					\
				../../engine/ServerEntity.cpp		\
				../../engine/CustomRect.cpp			\
				../../EntityLoad.cpp				\

CXXFLAGS 	=	-Wall -Wextra -I../../engine -I../../../interface -fPIC
NAME 		= 	BidosSlaves.so

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) -shared $(CXXFLAGS)
	g++ -o a.out  $(OBJ) main.cpp -I../../engine/ -I../../../interface -I../../ -ldl -g3
	rm -f $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all

.PHONY: all clean fclean re
