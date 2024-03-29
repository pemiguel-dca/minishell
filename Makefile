CC=cc
CFLAGS=-Wall -Wextra -Werror -fsanitize=address

LIBFT=libft/libft.a
GET_NEXT_LINE=get_next_line/get_next_line.a
RM=rm -f

NAME=minishell
SRCS=main.c vector.c signals.c\
lexer/lexer.c lexer/lexer_expander.c lexer/lexer_rearrange.c \
parser/parser.c \
env_vars/envstuff.c \
expander/expander.c \
redirs/create_files.c redirs/redir_out_append.c redirs/redir_in.c redirs/heredoc.c\
executer/executer.c executer/executer_utils.c \
builtins/cd.c builtins/pwd.c builtins/env.c builtins/unset.c builtins/export.c builtins/exit.c builtins/echo.c\

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) --no-print-directory bonus -C libft

$(GET_NEXT_LINE):
	$(MAKE) --no-print-directory -C get_next_line

$(NAME): $(OBJS) $(LIBFT) $(GET_NEXT_LINE)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GET_NEXT_LINE) -lreadline -o $(NAME)

clean:
	$(MAKE) clean -C libft
	$(MAKE) clean -C get_next_line
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C get_next_line
	$(RM) $(NAME)

run: all clean
	./minishell

re: fclean all
