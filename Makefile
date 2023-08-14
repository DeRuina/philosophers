# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: druina <druina@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 14:19:21 by druina            #+#    #+#              #
#    Updated: 2023/08/14 10:39:17 by druina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c utils.c init.c threads.c monitor.c

MANPATH = $(addprefix ./src/, $(SRC))

FLAGS = -Wall -Wextra -Werror

HEADER = ./src/philo.h

SANITIZER = -fsanitize=address

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(MANPATH) $(HEADER)
	@cc $(FLAGS) -o $(NAME) $(MANPATH) -pthread $(SANITIZER)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug: FLAGS += -g
debug: re 
