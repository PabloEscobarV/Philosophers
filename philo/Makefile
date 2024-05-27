# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/18 16:35:38 by blackrider        #+#    #+#              #
#    Updated: 2024/05/27 11:03:39 by polenyc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCDIR = src
OBJDIR = obj
HDRDIR = hdrs

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

CC = gcc
CFLAGS = -Wall -Wextra -I$(HDRDIR) -lpthread
LDFLAGS = -lpthread
FSANITFLAGS = -fsanitize=thread

.PHONY: all re clean fclean bonus

all: $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -c -g $(CFLAGS) $< -o $@

