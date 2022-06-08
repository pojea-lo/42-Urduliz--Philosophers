# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 16:04:11 by pojea-lo          #+#    #+#              #
#    Updated: 2022/06/07 07:59:08 by pojea-lo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAME_BONUS = philo_bonus

SRC = 	philo.c\
		philo_utils_0.c\
		philo_utils_1.c\
		philo_utils_2.c\
		philo_utils_3.c

SRC_BONUS = philo_bonus.c\
			philo_utils_0_bonus.c\
			philo_utils_1_bonus.c\
			philo_utils_2_bonus.c\
			philo_utils_3_bonus.c

OBJ = $(SRC: .c=.o)  

OBJ_BONUS = $(SRC_BONUS: .c=.o)  

CC = gcc
FLAGS = -Wall -Werror -Wextra -g -pthread
SAN = -g3 -fsanitize=address

RM = rm -r -f

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -c $(OBJ) $(SRC)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) #$(SAN)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(FLAGS) -c $(OBJ_BONUS) $(SRC_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) #$(SAN)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME_BONUS) $(NAME)
	$(RM) *.dSYM

re:	fclean all 

phony: name, all, clean, fclean, re, bonus 

