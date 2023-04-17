/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:12:05 by pemiguel          #+#    #+#             */
/*   Updated: 2023/04/17 20:30:53 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void	free_vars(char **path_env)
{
	size_t	i;

	i = 0;
	while (path_env[i])
	{
		free(path_env[i]);
		i++;
	}
	free(path_env);
}

t_executer	*initialize_executer_params(t_vec *expressions)
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
	if (files_to_be_created(expressions) && params->i == 0)
		params->new_files = create_files(expressions);
	else
		params->new_files = NULL;
	return (params);
}

char	*bin_path(const char *bin, t_expression *expr, t_vec *env)
{
	char		*full_path;
	char		**path_env;
	size_t		i;

	if (is_binary((char *)expr->args.buf[0]))
		return (expr->args.buf[0]);
	else if (pos_env_var(env, "PATH") != -1)
	{
		path_env = ft_split(env->buf[pos_env_var(env, "PATH")], ':');
		i = 0;
		while (path_env[i])
		{
			full_path = ft_strjoin(path_env[i], bin);
			if (access(full_path, F_OK) == 0)
			{
				free_vars(path_env);
				return (full_path);
			}
			free(full_path);
			i++;
		}
		free_vars(path_env);
	}
	return (NULL);
}

void	execute_cmd(t_expression *expr, t_vec *env, char *path)
{
	if (!is_child_builtin(expr->args.buf[0]))
	{
		vec_push(env, 0);
		vec_push(&expr->args, 0);
		execve(path, (char **)expr->args.buf, (char **)env->buf);
	}
	else
		execute_child_builtin(expr, env);
	free(path);
}
