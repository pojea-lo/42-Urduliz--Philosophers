NAME = philo

SRC = 	philo.c\
		philo_utils_0.c

OBJ = $(SRC: .c=.o)  

CC = gcc
FLAGS = -Wall -Werror -Wextra -g -pthread
SAN = -g3 -fsanitize=address

RM = rm -r -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -c $(OBJ) $(SRC)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(SAN)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)
	$(RM) *.dSYM

re:	fclean all

phony: name, all, clean, fclean, re 

