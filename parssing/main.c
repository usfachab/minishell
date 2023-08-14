/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:26:45 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 12:46:58 by yachaab          ###   ########.fr       */
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
		g_glob.exit_status = 130;
	}
}

t_parser_var	*intitial_and_signals(t_parser_var *var, char **env)
{
	var = malloc(sizeof(t_parser_var));
	g_glob.envp = NULL;
	var->pid = NULL;
	if (!var)
	{
		write(2, "minishell: ", 11);
		perror("");
		exit(ENOMEM);
	}
	init_var_with_env_variable(env);
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
			exit(g_glob.exit_status);
		if (*input && syntax_err(input))
		{
			add_history(input);
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
	var = intitial_and_signals(var, env);
	sig();
	the_main_loop(var, input);
	free(g_glob.envp);
	free(var);
	return (0);
}
			// while (var && var->data)
			// {
			// 	int i = 0;
			// 	while (var->data->cmd_args && var->data->cmd_args[i])
			// 	{
			// 		printf("command and args:%s\n", var->data->cmd_args[i]);
			// 		i++;
			// 	}
			// 	while (var->data && var->data->file)
			// 	{
			// 		printf("file_name: %s | file_type: %d\n",
			// 		var->data->file->file_name, var->data->file->type);
			// 		var->data->file = var->data->file->next;
			// 	}
			// 	printf("------------ next command ----------\n");
			// 	var->data = var->data->next;
			// }