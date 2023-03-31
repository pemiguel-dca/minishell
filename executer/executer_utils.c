/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:12:05 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/31 15:15:09 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void	free_vars(char **path_env, char *with_delim)
{
	size_t	i;

	i = 0;
	while (path_env[i])
	{
		free(path_env[i]);
		i++;
	}
	free(path_env);
	free(with_delim);
}

t_executer	*initialize_executer_params(t_vec *expressions, size_t executer_res)
{
	t_executer	*params;

	params = malloc(sizeof(t_executer));
	params->i = 0;
	params->input_fd = STDIN_FILENO;
	params->output_fd = STDOUT_FILENO;
	if (count_delims(expressions))
		params->delims = get_delimiters(expressions);
	params->pos_file = 0;
	params->exit = 0;
	if (files_to_be_created(expressions) && params->i == 0 && !executer_res)
		params->new_files = create_files(expressions);
	else
		params->new_files = NULL;
	return (params);
}

char	*bin_path(t_expression *expr, t_vec *env)
{
	char		*res;
	char		*with_delim;
	char		*full_path;
	char		**path_env;
	size_t		i;

	res = NULL;
	with_delim = ft_strjoin("/", (char *)expr->args.buf[0]);
	path_env = ft_split(env->buf[pos_env_var(env, "PATH")], ':');
	i = 0;
	while (path_env[i])
	{
		full_path = ft_strjoin(path_env[i], with_delim);
		if (access(full_path, F_OK) == 0)
		{
			res = full_path;
			break ;
		}
		free(full_path);
		i++;
	}
	free_vars(path_env, with_delim);
	return (res);
}

void	execute_cmd(t_expression *expr, t_vec *env, char *path,
	t_executer *params)
{
	if (!is_child_builtin(expr->args.buf[0]))
	{
		vec_push(env, 0);
		vec_push(&expr->args, 0);
		execve(path, (char **)expr->args.buf, (char **)env->buf);
	}
	else
		execute_child_builtin(expr, env, params);
	free(path);
}
