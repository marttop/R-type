##
## EPITECH PROJECT, 2021
## B-CPP-501-NCE-5-1-rtype-antonin.fille
## File description:
## Makefile
##

SRC			=	Heal.cpp					\
				../../engine/ServerEntity.cpp		\
				../../engine/CustomRect.cpp			\
				../../engine/EntityLoad.cpp				\

CXXFLAGS 	=	-Wall -Wextra -I../../engine -I../../../interface -fPIC
NAME 		= 	Heal.so

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
