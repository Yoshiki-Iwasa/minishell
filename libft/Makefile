# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yiwasa <yiwasa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/24 15:06:45 by yiwasa            #+#    #+#              #
#    Updated: 2020/08/05 15:43:07 by yiwasa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCCL = gcc -Wall -Werror -Wextra
LIBC = ar rc
SRCS =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c\
		ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
		ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c\
		ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c\
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c\
		ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c\
		ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c\
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c\

BONUS			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c
OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS:.c=.o}
NAME = libft.a								

.c.o:
	${GCCL} -c $<  -o $@ -I libft.h

all: ${NAME}

clean: 
	rm -f ${OBJS} ${BONUS_OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

bonus : ${OBJS} ${BONUS_OBJS}
	${LIBC} ${NAME} ${OBJS} ${BONUS_OBJS}


norme:
	norminette

$(NAME) : ${OBJS}
	${LIBC} ${NAME} ${OBJS}

.PHONY: all clean fclean re bonus
