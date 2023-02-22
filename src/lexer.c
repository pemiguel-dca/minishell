#include "minishell.h"

/*Atribuir os tokens, dividir o input em tokens basicamente, espaço também conta como um token */

t_tokens	append_list(t_tokens **head, char *content)
{
	
}

t_tokens	*atribute_tokens(char *input)
{
	t_tokens	*tokens;
	char		**args;
	int			i;

	i = 0;
	tokens = malloc(sizeof(t_tokens));
	args = ft_split(input, ' ');
	while (args[i])
		i++;
	i = 0;

	while (args[i])
	{
		//usar append list...
		tokens->token = ft_strdup(args[i]);
		tokens->next = tokens;
		i++;
	}
}
