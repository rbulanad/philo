# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 14:03:34 by rbulanad          #+#    #+#              #
#    Updated: 2024/02/21 19:25:22 by rbulanad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philosophers
SRC 		= main.c \
		  funcs/ft_atol.c \
		  utils.c
OBJ		= ${SRC:.c=.o}
RM		= rm -f
CC		= gcc
CFLAGS		= -Wall -Wextra -Werror 

ifdef MAKEBONUS
	CFLAGS += -fsanitize=thread -g
endif

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

all: ${NAME}

debug:
	@${MAKE} MAKEBONUS=1 re

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
