# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 19:31:00 by aben-nei          #+#    #+#              #
#    Updated: 2023/05/26 21:50:48 by arabiai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -Wno-misleading-indentation #-fsanitize=address
#  -Wno-misleading-indentation

RFLAGS = -lreadline

SOURCE_BUILT_IN = execution/built_in_functions/my_export.c execution/built_in_functions/my_env.c execution/built_in_functions/my_unset.c \
				execution/built_in_functions/my_pwd.c execution/built_in_functions/my_cd.c execution/built_in_functions/my_echo.c execution/built_in_functions/my_exit.c

# source files
SRC_DYALI = utils/utils4.c utils/utils1.c utils/utils2.c utils/utils3.c execution/help_export.c execution/help_env.c $(SOURCE_BUILT_IN)


SRCS = main/main.c parsing/ft_trim_quotes.c parsing/ft_expand.c utils/utils.c parsing/ft_token.c parsing/syntex_error.c\
	parsing/check_quotes.c parsing/rederection.c parsing/heredoc.c parsing/command_table.c $(SRC_DYALI)

OBJS = $(SRCS:.c=.o)

LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $(RFLAGS) $(OBJS) $(LIB) -o $(NAME)
	@clear
	@echo -e "\033[32m[OK] \033[0mCompilation done"

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@
	@clear

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	@clear
	@echo -e "\033[32m[OK] \033[0mCleaning done"

re: fclean all