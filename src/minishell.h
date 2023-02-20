#ifndef MINISHELL_H
# define MINISHELL_H

/*Todos os "tokens" que vamos usar */
# define SEP " "
# define QUOTE "'"
# define DOUBLE_QUOTE """
# define REDIR_OUT ">"
# define REDIR_IN "<"
# define REDIR_APPEND ">>"
# define REDIR_DELIMITER "<<"
# define PIPE "|"

/*Estrutura para os builtins*/

typedef struct s_builtins
{

	char	**argument;

}	t_builtins;

/*Precisamos de uma estrutura para guardar as variaveis de ambiente*/

typedef struct			s_env
{
	char	*name;
	char	*value;
}	t_env;


#endif