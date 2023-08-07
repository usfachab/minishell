/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.0.0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:53:17 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/05 18:20:22 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static void	make_arg_a_env_variable(char *arg, t_list *env, t_parser_var *var)
{
	var->size = 0;
	if (env && arg)
	{
		var->equal = strchr(arg, '=');
		if (var->equal)
		{
			if ((*(var->equal - 1)) == '+')
				ft_help_1(arg, env, var);
			else
				ft_help_2(arg, env, var);
		}
		else
		{
			handling_solo_variable(arg, env);
		}
	}
}

static int	check_if_variable_is_valid(char *cmd)
{
	if (!alphaunder(*cmd))
		return (0);
	if (!alphanumunder(cmd))
		return (0);
	return (1);
}

static void	add_arg_to_env_list(char **cmd, t_list *env, t_parser_var *var)
{
	while (cmd && *cmd)
	{
		if (check_if_variable_is_valid(*cmd))
		{
			make_arg_a_env_variable(*cmd, env, var);
		}
		else
			printf("export: `%s': not a valid identifier\n", *cmd);
			
		cmd++;
	}
}

static void	show_exported_variables(t_list *env)
{
	t_list	*tmp;
	char	*first;
	char	*last;
	int		size;

	tmp = env;
	while (tmp)
	{
		if (tmp->content)
		{
			if (ft_strchr(tmp->content, '='))
			{
				last = ft_strchr(tmp->content, '=') + 1;
				size = (last - tmp->content);
				first = ft_strdup(tmp->content);
				first[size] = 0;
				printf("declare -x %s\"%s\"\n", first, last);
				free(first);
				first = NULL;
			}
			else
				printf("declare -x %s\n", tmp->content);
		}
		tmp = tmp->next;
	}
}

void	_export(t_parser_var *var)
{
	t_list	*env;
	char	**cmd;

	env = var->env;
	cmd = var->data->cmd_args;
		// printf(">>>>>>>>>>>\n");
	if (!(*(cmd + 1)))
		show_exported_variables(env);
	else
		add_arg_to_env_list(cmd + 1, env, var);
	if ((*(cmd + 1)))
		convert_to_array(var);
}