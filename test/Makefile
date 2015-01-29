# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbersac <gbersac@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/22 13:15:39 by gbersac           #+#    #+#              #
#    Updated: 2015/01/28 14:13:45 by gbersac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# BASIC VARIABLES															   #
################################################################################

NAME				:= test

SRCS				:= main.c test.c

PATH_OBJ			:= obj
PATH_SRC			:= src
PATH_INC			:= inc

CFLAGS				:= -Wall -Wextra -Werror
OBJECTS				:= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRCS))

################################################################################
# LIBRARY VARIABLES															   #
################################################################################

export DIR_MALLOC	:= ../$(DIR_MALLOC)

LIB_MALLOC			:= -L$(DIR_MALLOC) -lft_malloc

export DIR_LIB 		:= $(patsubst %,../%,$(DIR_LIB))
LIBRARY				:= $(LIB_MALLOC)
INCLUDES			:= -I./$(PATH_INC) $(patsubst %,-I%/inc,$(DIR_LIB))

################################################################################
# BASIC RULES																   #
################################################################################

.PHONY: all

all: $(NAME)

$(NAME): $(OBJECTS)
	cc -o $@ $(OBJECTS) $(LIBRARY) $(DEBUG)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	@echo $(DIR_LIB)
	cc -c -o $@ $(CFLAGS) $^ $(DEBUG) $(INCLUDES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
