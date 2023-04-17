/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnobre-m <pnobre-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:21:18 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/04/17 20:58:19 by pnobre-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "lexer/lexer.h"
#include "executer/executer.h"
#include "builtins/builtins.h"
#include "expander/expander.h"
#include "env_vars/env.h"
#include "globals.h"

t_signals	g_signals;

void	__debug_lexer(const t_vec *tokens)
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

// void	__debug_parser(const t_vec *expressions)
// {
// 	for (size_t i = 0; i < expressions->len; i += 1)
// 	{
// 		printf("[");
// 		t_expression *expr = expressions->buf[i];
// 		for (size_t j = 0; j < expr->args.len; j += 1)
// 		{
// 			char *arg = expr->args.buf[j];
// 			printf("'%s'", arg);
// 			if (j + 1 != expr->args.len)
// 				printf(", ");
// 		}
// 		printf(" | State = %u", expr->state);
// 		printf("]\n");
// 	}
// }

// void __debug_envs(const t_vec *env)
// {
// 	printf("[");
// 	for (size_t i = 0; i < env->len; i += 1)
// 	{
// 		printf("'%s'", (char *)env->buf[i]);
// 		if (i + 1 != env->len)
// 			printf(", ");
// 	}
// 	printf("]\n");
// }

static void	free_all(t_vec *expressions,
				t_executer *params,
				t_vec *tokens,
				char *input
)
{
	size_t		i;

	i = 0;
	while (i < expressions->len)
	{
		vec_free(&((t_expression *)expressions->buf[i])->args);
		i += 1;
	}
	if (count_delims(expressions))
	{
		free_delims(params->delims);
		unlink("heredoc.tmp");
	}
	vec_free(expressions);
	vec_free(tokens);
	free(input);
	free(params->new_files);
	free(params);
}

static size_t	process(t_vec *env, const char *input)
{
	size_t		should_exit;
	t_vec		tokens;
	t_vec		expressions;
	t_executer	*params;

	tokens = trim_empty(tokenize(env, input));
	// __debug_lexer(&tokens);
	expressions = parse(&tokens);
	expander(&expressions, env);
	params = initialize_executer_params(&expressions);
	if (!expressions.len)
		g_signals.exit_status = 0;
	else if (!check_errors_parser(&expressions))
		executer(&expressions, params, env);
	should_exit = params->exit;
	free_all(&expressions, params, &tokens, (char *)input);
	return (should_exit);
}

static void	set_pid(void)
{
	g_signals.pid = 14;
	if (g_signals.pressed_in_child)
	{
		printf("\n");
		g_signals.pressed_in_child = false;
	}
}

void	loop(t_vec *env)
{
	char	*input;

	while (true)
	{
		set_pid();
		input = readline("▲ " COLOR_BOLD COLOR_CYAN "$" COLOR_OFF " ");
		if (!input)
		{
			printf("exit\n");
			free(input);
			break ;
		}
		else if (ft_is_all_whitespace(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (process(env, input))
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_vec		env;

	(void)argc;
	(void)argv;
	signal(SIGINT, sig_int);
	g_signals = (t_signals){
		.pressed_in_child = false,
		.exit_status = 0,
		.is_heredoc = false
	};
	env = create_envs(envp);
	loop(&env);
	vec_free(&env);
	return (g_signals.exit_status);
}

// TODO: echo '|' !
