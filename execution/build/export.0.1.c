/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.0.1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:55:49 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:51:21 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	handling_plus_equle_part(t_parser_var *var, char *arg)
{
	var->last_saved = ft_strchr(var->altered_node->content, '=');
	if (var->last_saved)
	{
		var->tmp = ft_strjoin(var->last_saved, var->last);
		free(var->altered_node->content);
		var->altered_node->content = ft_strjoin(var->first, var->tmp);
		free(var->first);
		free(var->tmp);
	}
	else
	{
		var->tmp = ft_strjoin(var->altered_node->content,
				ft_strchr(arg, '='));
		free(var->altered_node->content);
		var->altered_node->content = ft_strdup(var->tmp);
		free(var->first);
		free(var->tmp);
	}
}

void	ft_help_1(char *arg, t_list *env, t_parser_var *var)
{
	var->last = ft_strchr(arg, '=') + 1;
	var->size = (var->last - arg) - 2;
	var->first = ft_strdup(arg);
	var->first[var->size] = 0;
	var->altered_node = check_for_variable_existance(var->first, env);
	if (var->altered_node)
		handling_plus_equle_part(var, arg);
	else
	{
		var->tmp = ft_strjoin("", var->last - 1);
		ft_lstadd_back(&env, ft_lstnew(ft_strjoin(var->first, var->tmp)));
		free(var->tmp);
		free(var->first);
	}
}

/* 		function name: make_arg_a_env_variable_h2	*/

void	ft_help_2(char *arg, t_list *env, t_parser_var *var)
{
	var->last = ft_strdup((strchr(arg, '=') + 1));
	arg[ft_strchr(arg, '=') - arg + 1] = 0;
	var->first = arg;
	var->variable = ft_strjoin(var->first, var->last);
	free(var->last);
	var->altered_node = check_for_variable_existance(var->first, env);
	if (var->variable && var->altered_node)
	{
		free(var->altered_node->content);
		var->altered_node->content = ft_strdup(var->variable);
		free(var->variable);
	}
	else
		ft_lstadd_back(&env, ft_lstnew(var->variable));
}
