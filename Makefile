CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS = change_into_array.c \
		command_cd.c \
		command_echo.c \
		command_env.c \
		command_exit.c \
		command_export.c \
		command_multi.c \
		command_pwd.c \
		command_shell.c \
		command_unset.c \
		escape.c \
		escape2.c \
		free.c \
		get_next_line.c \
		get_next_line_utils.c \
		list.c \
		list2.c \
		main.c \
		manage_fd.c \
		pipe.c \
		read_command.c \
		redirect.c \
		sell_execution.c \
		signal_handle.c \
		utils.c \
		utils2.c
OBJS = ${SRCS:.c=.o}
NAME = minishell
LIBFT = ./libft/libft.a


all: ${NAME}

$(NAME) : ${OBJS}
	$(MAKE) bonus -C ./libft
	mv $(LIBFT) .
	$(CC) -o $(NAME) $(OBJS) libft.a

clean:
	$(MAKE) clean -C ./libft
	rm -rf ${OBJS}

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf libft.a
	rm  -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
