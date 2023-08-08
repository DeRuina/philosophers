# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: druina <druina@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 14:19:21 by druina            #+#    #+#              #
#    Updated: 2023/08/08 15:38:35 by druina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c utils.c

MANPATH = $(addprefix ./src/, $(SRC))

FLAGS = -Wall -Wextra -Werror

HEADER = ./src/philo.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(MANPATH)
	@cc $(FLAGS) -o $(NAME) $(MANPATH) $(HEADER) -pthread 

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug: FLAGS += -g
debug: re 
