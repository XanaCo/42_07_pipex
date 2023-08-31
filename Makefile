# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 18:07:11 by ancolmen          #+#    #+#              #
#    Updated: 2023/05/25 12:33:43 by ancolmen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#######	VARIABLES #######

NAME		= pipex
LIBFT		= libft.a

LFT_PATH	= ./libft/
INC_PATH	= ./include
SRC_PATH	= ./src/

SRC			= ${SRC_PATH}main.c \
				${SRC_PATH}check_and_stock.c \
				${SRC_PATH}start.c \
				${SRC_PATH}utils.c \
				${SRC_PATH}exit.c


OBJ			= ${notdir ${SRC:.c=.o}}

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CFI 		= -I${INC_PATH}

RM			= rm -rf

#######	RULES #######

${NAME}: ${OBJ} ${LFT_PATH}${LIBFT}
	@ echo "-----Pipex in progress-----"
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} ${LFT_PATH}${LIBFT}

${OBJ}: ${SRC}
	@ echo "-----Creating objects-----"
	${CC} ${CFLAGS} -c -I${INC_PATH} ${SRC}

${LFT_PATH}${LIBFT}:
	@ echo "-----Creating LIBFT-----"
	@make -C ${LFT_PATH}


all: ${NAME}

bonus: all

clean:
	@make clean -C ${LFT_PATH}
	${RM} ${OBJ}

fclean: clean
	@make fclean -C ${LFT_PATH}
	${RM} ${NAME}

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
