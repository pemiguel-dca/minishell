SRCS=get_next_line.c get_next_line_utils.c 
OBJS=$(SRCS:.c=.o)

CC=cc
C_FLAGS=-Wall -Wextra -Werror
RM=rm -f

NAME=get_next_line.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all