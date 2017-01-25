# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arosset <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/19 10:57:49 by arosset           #+#    #+#              #
#    Updated: 2016/12/19 10:57:54 by arosset          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	libftprintf.a

CC 			=	gcc
CFLAGS 		= 	-Wall -Werror -Wextra

INCLUDES 	= 	ft_printf.h

SRC 		= 	ft_printf.c
OBJ 		= 	$(SRC:.c=.o)

# COLORS
C_NO		=	"\033[00m"
C_OK		=	"\033[35m"
C_GOOD		=	"\033[32m"
C_ERROR		= 	"\033[31m"
C_TEST		= 	"\033[33m"

# MESSAGE
SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK 			=	$(C_OK)OK$(C_NO)
F_TEST 		= 	$(C_TEST)DEBUT TEST$(C_NO)
ERROR		= 	$(C_ERROR) ERROR $(C_NO)
C_DEL		= 	$(C_ERROR) DELETE $(C_NO)
C_OBJ		= 	$(C_OK) OBJ $(NAME) $(C_NO)

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo Lib : [ $(NAME) ] $(SUCCESS)

%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDES)
	@echo $(C_OBJ) [ $< ] $(OK)
clean :
	@rm -f $(OBJ)
	@echo $(C_DEL) OBJ $(NAME)

fclean : clean
	@rm -f $(NAME)
	@echo $(C_DEL) $(NAME)

re : fclean all

.PHONY: clean, fclean, re
