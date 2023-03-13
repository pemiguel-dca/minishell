/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:21:18 by pnobre-m          #+#    #+#             */
/*   Updated: 2023/03/13 14:39:10 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "builtins/builtins.h"
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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	// t_list		*env;
	t_vec		tokens;
	t_vec		expressions;
	t_list		*final;
	char		*input;

	while (true)
	{
		input = readline("▲ " COLOR_BOLD COLOR_CYAN "$" COLOR_OFF " ");
		add_history(input);
		tokens = tokenize(input);
		// __debug_lexer(&tokens);
		expressions = parse(&tokens);
		expressions = dumb_shit(&expressions);
		//__debug_parser(&expressions);
		//in the future add this to 'spawn'
		//env = create_envs(envp);
		//if (ft_strcmp("env",parser->args[0]) == 0)
		//	_env(&env);
		//else if (ft_strcmp("pwd",parser->args[0]) == 0)
		//	_pwd(parser);
		//else if (ft_strcmp("cd",parser->args[0]) == 0)
		//	_cd(parser);
		// else
		/*problem with this, when parser as an error the next cmd does not work (???)
		The real problem is that, for example if u write '>' it prints the erros but the next state is going to be a FL*/
		if (!check_errors_parser(&expressions))
			spawn(&expressions, STDIN_FILENO, STDOUT_FILENO);
		vec_free(&expressions);
		vec_free(&tokens);
		free(input);
	}
	return (0);
}

// TODO: 	manage env vars
//			finish parser w other modes
//
