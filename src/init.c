#include "minishell.h"

t_info	*init_struct(char *input)
{
	t_info	*info;
	int		i;

	i = 0;
	info = malloc(sizeof(t_info));
	info->env_v = malloc(sizeof(t_env));
	info->args = ft_split(input, ' ');

	return (info);
}
