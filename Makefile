# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/17 22:29:44 by nkamolba          #+#    #+#              #
#    Updated: 2017/12/17 22:59:48 by nkamolba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_contrast
LIBFT = libft/libft.a
THPOOL = libft_thpool/libft_thpool.a

CFLAGS = -Wall -Wextra -Werror
INCLUDE = -Llibft -lft -Llibft_thpool -lft_thpool -lpthread

THPOOL_F = threadpool.c ft_data.c ft_task.c
CONTRAST_F = main.c process.c ft_contrast.c

THPOOL_C = $(addprefix libft_thpool/, $(THPOOL_F))
CONTRAST_C = $(addprefix contrast/, $(CONTRAST_F))

THPOOL_O = $(THPOOL_C:%.c=%.o)
CONTRAST_O = $(CONTRAST_C:%.c=%.o)

all: $($LIBFT) $(THPOOL) $(NAME)

$(LIBFT):
	@make -C libft

$(THPOOL): $(THPOOL_O) | $(LIBFT)
	ar rc $(THPOOL) $^
	ranlib $(THPOOL)

$(NAME): $(CONTRAST_O) | $(THPOOL) $(LIBFT)
	gcc $(CLANGS) -o $(NAME) $(CONTRAST_O) $(INCLUDE)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	rm -f $(THPOOL_O)
	rm -f $(CONTRAST_O)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(THPOOL)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
