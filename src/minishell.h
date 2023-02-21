#ifndef MINISHELL_H
# define MINISHELL_H

/* Libs */
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>

/* Colors */
# define COLOR_BOLD "\e[1m"
# define COLOR_CYAN "\x1b[36m"
# define COLOR_OFF  "\e[m"

/*Todos os "tokens" que vamos usar */
# define SEP " "
# define QUOTE "'"
# define DOUBLE_QUOTE '"'
# define REDIR_OUT ">"
# define REDIR_IN "<"
# define REDIR_APPEND ">>"
# define REDIR_DELIMITER "<<"
# define PIPE "|"

/* Builtins, the only one that takes account options is echo "-n" */

# define UNSET "unset"
# define ECHO "echo"
# define PWD "pwd"
# define CD "cd"
# define EXPORT "export"
# define ENV "env"
# define EXIT "exit"

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

/* Estrutura que guarda a informacao sobre o input*/
typedef struct s_info
{
	int		status; //should be aware of single quotes or double quotes
	char	**args; //saves the input separated by spaces
	int		redirs; //takes account if there are any redirections
	int		pipes; //takes account if there are pipes in the input
	t_env	*env_v;
}		t_info;

#endif
