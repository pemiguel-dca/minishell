LIB_SRCS=	ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memchr.c ft_memmove.c ft_putendl_fd.c ft_split.c ft_striteri.c ft_strlcpy.c ft_strncmp.c ft_strtrim.c	\
			ft_toupper.c ft_bzero.c ft_isalpha.c ft_isprint.c ft_memcmp.c ft_memset.c ft_putnbr_fd.c ft_strchr.c ft_strjoin.c ft_strlen.c ft_strnstr.c		\
			ft_substr.c ft_calloc.c ft_isascii.c ft_itoa.c ft_memcpy.c ft_putchar_fd.c ft_putstr_fd.c ft_strdup.c ft_strlcat.c ft_strmapi.c ft_strrchr.c	\
			ft_tolower.c ft_isspace.c ft_swap.c ft_strcmp.c ft_is_all_whitespace.c
LIB_OBJS=$(LIB_SRCS:.c=.o)

BONUS_SRCS=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
BONUS_OBJS=$(BONUS_SRCS:.c=.o)

CC=cc
C_FLAGS=-Wall -Wextra -Werror
RM=rm -f

NAME=libft.a

all: $(NAME)

$(NAME): $(LIB_OBJS)
	ar rc $(NAME) $(LIB_OBJS)

bonus: $(LIB_OBJS) $(BONUS_OBJS)
	ar rc $(NAME) $(LIB_OBJS) $(BONUS_OBJS)

clean:
	$(RM) $(LIB_OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
