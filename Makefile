##
## EPITECH PROJECT, 2019
## Makefile plazza
## File description:
## Makefile plazza
##

NAME	=	plazza

CPPFLAGS	=	-W -Wall -Wextra -I ./include/ -l pthread

SRC	=	src/main.cpp	\
		src/Cook/Cook.cpp	\
		src/Encapsulation/Pipe.cpp	\
		src/Encapsulation/Mutex.cpp	\
		src/Reception/Reception.cpp	\
		src/Reception/Log.cpp	\
		src/Encapsulation/Write.cpp	\
		src/Encapsulation/Read.cpp

OBJ	=	$(SRC:.cpp=.o)

RM	=	rm -rf

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(OBJ) $(NAME)

re:	fclean all
