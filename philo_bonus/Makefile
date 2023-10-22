# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 00:10:23 by doriani           #+#    #+#              #
#    Updated: 2023/10/22 10:44:03 by doriani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############
## Variables ##
###############
NAME		= philo_bonus
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I./includes/
SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
SRC_FILES   = philo_bonus validators_bonus init_bonus routine_bonus utils_bonus
OBJ_FILES	= $(SRC_FILES:.c=.o)
SRCS		= $(addsuffix .c, $(addprefix $(SRC_DIR), $(SRC_FILES))) 
OBJS		= $(addsuffix .o, $(addprefix $(OBJ_DIR), $(OBJ_FILES)))
LIBRARIES	= -lpthread

#############
## Targets ##
#############
usage:
	@echo "Usage: make [usage | all | philo_bonus | clean | fclean | re]"
	@echo
	@echo "-- Usage --"
	@echo "\tusage: displays this message"
	@echo
	@echo "-- Philosophers build targets --"
	@echo "\tall: compiles philosophers with bonus"
	@echo "\tphilo_bonus: compiles philosophers with bonus"
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
