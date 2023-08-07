/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:26:45 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/02 18:50:49 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/lib.h"

void	sighandler(int sig)
{
	if (sig == SIGINT && g_glob.interapt_main_signal != -99)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

t_parser_var	*intitial_and_signals(t_parser_var *var, char **env)
{
	var = malloc(sizeof(t_parser_var));
	var->envp = NULL;
	var->pid = NULL;
	if (!var)
	{
		perror("");
		exit(ENOMEM);
	}
	init_var_with_env_variable(var, env);
	return (var);
}

void	sig(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	disable_echo_int();
}

void	the_main_loop(t_parser_var *var, char *input)
{
	while (1)
	{
		g_glob.interapt_main_signal = 0;
		input = readline("minishell -> ");
		if (!input)
			exit(0);
		add_history(input);
		if (*input && syntax_err(input))
		{
			var = parser(input, var);
			execution(var);
			reset(var);
		}
		free(input);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char			*input;
	t_parser_var	*var;

	(void)argc;
	(void)argv;
	var = NULL;
	input = NULL;
	(void)env;
	var = intitial_and_signals(var, env);
	sig();
	the_main_loop(var, input);
	free(var->envp);
	free(var);
	return (0);
}
