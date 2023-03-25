/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:21:18 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/03/24 21:47:41 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "executer/executer.h"
#include "builtins/builtins.h"
#include "expander/expander.h"
#include "env_vars/env.h"
#include "globals.h"

/*
void __debug_lexer(const t_vec *tokens)
{
	printf("[");
	for (size_t i = 0; i < tokens->len; i += 1)
	{
		printf("'%s'", (char *)tokens->buf[i]);
		if (i + 1 != tokens->len)
			printf(", ");
	}
	printf("]\n");
}
*/
void	__debug_parser(const t_vec *expressions)
{
	for (size_t i = 0; i < expressions->len; i += 1)
	{
		printf("[");
		t_expression *expr = expressions->buf[i];
		for (size_t j = 0; j < expr->args.len; j += 1)
		{
			char *arg = expr->args.buf[j];
			printf("'%s'", arg);
			if (j + 1 != expr->args.len)
				printf(", ");
		}
		printf(" | State = %u", expr->state);
		printf("]\n");
	}
}
/*
void __debug_envs(const t_vec *env)
{
	printf("[");
	for (size_t i = 0; i < env->len; i += 1)
	{
		printf("'%s'", (char *)env->buf[i]);
		if (i + 1 != env->len)
			printf(", ");
	}
	printf("]\n");
}
*/

void	free_all(t_vec expressions, t_executer *params, t_vec tokens, char *input)
{
	size_t	i;

	i = 0;
	while (i < expressions.len)
	{
		vec_free(&((t_expression *)expressions.buf[i])->args);
		i += 1;
	}	
	vec_free(&expressions);
	vec_free(&tokens);
	free(input);
	if (params->exit)
	{
		free(params->new_files);
		free(params);
		exit (0);
	}
	else
	{
		free(params->new_files);
		free(params);	
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_vec		env;
	t_vec		tokens;
	t_vec		expressions;
	t_executer	*params;
	char		*input;
	static int	last_exit_status;

	env = create_envs(envp);
	while (true)
	{
		input = readline("▲ " COLOR_BOLD COLOR_CYAN "$" COLOR_OFF " ");
		add_history(input);
		tokens = tokenize(input);
		// __debug_lexer(&tokens);
		expressions = parse(&tokens);
		expander(&expressions, &env, params);
		params = initialize_executer_params(&expressions);
		__debug_parser(&expressions);
		if (!check_errors_parser(&expressions))
		 	executer(&expressions, params, &env);
		free_all(expressions, params, tokens, input);
	}
	vec_free(&env);
	return (0);
}
