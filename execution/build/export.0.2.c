/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.0.2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:57:18 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:51:34 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

char	*generate_env_key(char *content)
{
	char	*env_start;
	char	*env_key_name;

	if (ft_strchr(content, '='))
	{
		env_start = ft_strdup(content);
		env_start[ft_strchr(env_start, '=') - env_start] = 0;
		env_key_name = ft_strdup(env_start);
		free(env_start);
		env_start = NULL;
	}
	else
		env_key_name = ft_strdup(content);
	return (env_key_name);
}

char	*generate_key(char *arg)
{
	char	*key_name;

	if (ft_strchr(arg, '='))
	{
		arg[ft_strchr(arg, '=') - arg] = 0;
		key_name = ft_strdup(arg);
	}
	else
		key_name = ft_strdup(arg);
	return (key_name);
}

t_list	*check_for_variable_existance(char *arg, t_list *env)
{
	char	*key_name;
	char	*env_key_name;
	t_list	*tenv;

	tenv = env;
	key_name = generate_key(arg);
	while (tenv)
	{
		if (tenv->content)
			env_key_name = generate_env_key(tenv->content);
		if (!ft_strcmp(key_name, env_key_name))
		{
			free(key_name);
			free(env_key_name);
			return (tenv);
		}
		else
		{
			free(env_key_name);
			env_key_name = NULL;
		}
		tenv = tenv->next;
	}
	free(key_name);
	return (NULL);
}

void	handling_solo_variable(char *cmd, t_list *env)
{
	t_list	*altered_node;

	altered_node = check_for_variable_existance(cmd, env);
	if (altered_node && (ft_strlen(altered_node->content) == ft_strlen(cmd)))
	{
		free(altered_node->content);
		altered_node->content = NULL;
		altered_node->content = ft_strdup(cmd);
	}
	else if (altered_node
		&& (ft_strlen(altered_node->content) != ft_strlen(cmd)))
		return ;
	else
		ft_lstadd_back(&env, ft_lstnew(strdup(cmd)));
}
