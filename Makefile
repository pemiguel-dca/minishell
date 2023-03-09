CC=cc
CFLAGS=#-Wall -Wextra -Werror

LIBFT=libft/libft.a
# GET_NEXT_LINE=get_next_line/get_next_line.a
RM=rm -f

NAME=minishell
SRCS=main.c vector.c \
lexer/lexer.c \
parser/parser.c parser/parser_utils.c \
env_vars/envstuff.c \
# redirs/redir_out.c \
# builtins/env.c builtins/pwd.c builtins/cd.c

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) --no-print-directory bonus -C libft

# $(GET_NEXT_LINE):
# 	$(MAKE) --no-print-directory -C get_next_line

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

clean:
	$(MAKE) clean -C libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME)

run: all clean
	./minishell

re: fclean all
