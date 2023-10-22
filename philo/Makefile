# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 00:10:23 by doriani           #+#    #+#              #
#    Updated: 2023/10/22 10:44:25 by doriani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############
## Variables ##
###############
NAME		= philo
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I./includes/
SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
SRC_FILES   = philo validators init utils routine threads
OBJ_FILES	= $(SRC_FILES:.c=.o)
B_OBJ_FILES = $(B_SRC_FILES:.c=.o)
SRCS		= $(addsuffix .c, $(addprefix $(SRC_DIR), $(SRC_FILES))) 
OBJS		= $(addsuffix .o, $(addprefix $(OBJ_DIR), $(OBJ_FILES)))
LIBRARIES	= -lpthread

#############
## Targets ##
#############
usage:
	@echo "Usage: make [usage | all | philo | clean | fclean | re]"
	@echo
	@echo "-- Usage --"
	@echo "\tusage: displays this message"
	@echo
	@echo "-- Philosophers build targets --"
	@echo "\tall: compiles philosophers"
	@echo "\tphilo: compiles philosophers"
	@echo "\tclean: remove object files"
	@echo "\tfclean: remove object files and programs"
	@echo "\tre: fclean and all"

all: $(NAME)

$(NAME):  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LIBRARIES)

$(OBJ_DIR)%o: $(SRC_DIR)%c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) $(LIBRARIES)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
