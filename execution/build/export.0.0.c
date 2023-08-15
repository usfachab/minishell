/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.0.0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:53:17 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:51:15 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static void	make_arg_a_env_variable(char *arg, t_list *env, t_parser_var *var)
{
	var->size = 0;
	if (env && arg)
	{
		var->equal = ft_strchr(arg, '=');
		if (var->equal)
		{
			if ((*(var->equal - 1)) == '+')
				ft_help_1(arg, env, var);
			else
				ft_help_2(arg, env, var);
		}
		else
			handling_solo_variable(arg, env);
	}
}

int	check_if_variable_is_valid(char *cmd)
{
	if (!alphaunder(*cmd))
	{
		g_glob.exit_status = 1;
		return (0);
	}
	if (!alphanumunder(cmd))
	{
		g_glob.exit_status = 1;
		return (0);
	}
	return (1);
}

static void	add_arg_to_env_list(char **cmd, t_list *env, t_parser_var *var)
{
	while (cmd && *cmd)
	{
		if (check_if_variable_is_valid(*cmd))
			make_arg_a_env_variable(*cmd, env, var);
		else
		{
			write(2, "export: `", 9);
			write(2, *cmd, ft_strlen(*cmd));
			write(2, "': not a valid identifier\n", 26);
			g_glob.exit_status = 1;
		}
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

void	_export(t_parser_var *var, t_data *data)
{
	t_list	*env;
	char	**cmd;

	env = g_glob.env;
	cmd = data->cmd_args;
	if (!(*(cmd + 1)))
		show_exported_variables(env);
	else
	{
		add_arg_to_env_list(cmd + 1, env, var);
		convert_to_array();
	}
}
