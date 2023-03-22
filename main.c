/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:21:18 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/03/22 18:49:02 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "executer/executer.h"
#include "builtins/builtins.h"
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

/*
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
*/

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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_vec		env;
	t_vec		tokens;
	t_vec		expressions;
	t_executer	*params;
	char		*input;

	env = create_envs(envp);
	while (true)
	{
		input = readline("▲ " COLOR_BOLD COLOR_CYAN "$" COLOR_OFF " ");
		add_history(input);
		tokens = tokenize(input);
		/*Find better names for this two functions*/
		expressions = parse(&tokens);
		// __debug_lexer(&tokens);
		// __debug_parser(&expressions);
		//__debug_envs(&env);
		// params = initialize_executer_params(&expressions);
		// if (!check_errors_parser(&expressions)) {}
			// executer(&expressions, params, &env);
		vec_free(&expressions);
		vec_free(&tokens);
		// free(params->new_files);
		// free(params);
		free(input);
	}
	vec_free(&env);
	return (0);
}
