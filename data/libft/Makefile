NAME = libft.a

CC = cc

FLAGS = -Werror -Wextra -Wall -g3

LIB = libft.h gnl/get_next_line.h printf/ft_printf.h

SRCS = ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
    	ft_isascii.c \
    	ft_isdigit.c \
    	ft_isprint.c \
    	ft_memset.c \
    	ft_strlen.c \
    	ft_memcpy.c \
    	ft_memmove.c \
    	ft_strlcpy.c \
    	ft_strlcat.c \
    	ft_toupper.c \
    	ft_tolower.c \
    	ft_strchr.c\
    	ft_strrchr.c \
    	ft_strncmp.c \
    	ft_memchr.c \
    	ft_memcmp.c \
    	ft_strnstr.c \
    	ft_atoi.c \
    	ft_calloc.c  \
		ft_strdup.c  \
		ft_substr.c  \
		ft_strjoin.c \
		ft_split.c \
    	ft_strtrim.c \
    	ft_itoa.c \
    	ft_strmapi.c \
    	ft_striteri.c \
    	ft_putchar_fd.c \
    	ft_putstr_fd.c \
    	ft_putendl_fd.c \
    	ft_putnbr_fd.c \
		ft_lstnew.c \
	    ft_lstadd_front.c \
	    ft_lstsize.c \
	    ft_lstlast.c \
	    ft_lstadd_back.c \
	    ft_lstdelone.c \
	    ft_lstclear.c \
	    ft_lstiter.c \
	    ft_lstmap.c  \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		printf/ft_libft.c \
		printf/ft_printf.c \
		printf/ft_putnbr_base.c\
		printf/ft_putnbr.c \
		ft_isspace.c\
		ft_intlen.c\
		ft_max.c\
		ft_min.c\
		ft_power.c\
		ft_strcmp.c\
		ft_vajoin.c\
		ft_free_tab.c\
		ft_strtablen.c\
		ft_swap_str.c\
		ft_strcat.c\
		ft_strprinttab.c\
		ft_abs.c\
		ft_absf.c\
		ft_tablen.c\
		ft_inset.c\
		ft_add_element_tab.c\
		ft_tabcpy.c

OBJS = ${SRCS:.c=.o}

all:  ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS} ${LIB}

.c.o:
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -f ${OBJS} ${BONUSOBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re
