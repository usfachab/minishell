/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.0.2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:57:18 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/09 12:59:41 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	alphaunder(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95)
		return (1);
	return (0);
}

int	alphanumunder(char *cmd)
{
	char	*equale;

	cmd = &(*(cmd + 1));
	equale = strchr(cmd, '=');
	while (equale && cmd && cmd < equale)
	{
		if (!alphaunder(*cmd) && (!((*cmd >= 48 && *cmd <= 57) || *cmd == '+')))
			return (0);
		cmd++;
	}
	return (1);
}

t_list	*check_for_variable_existance(char *var_name, t_list *env)
{
	while (env)
	{
		if (!ft_strchr(env->content, '='))
		{
			if (!ft_strncmp(var_name, env->content, strlen(var_name) - 1))
				return (env);
		}
		else if (!ft_strncmp(var_name, env->content, strlen(var_name)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	handling_solo_variable(char *cmd, t_list *env)
{
	t_list	*altered_node;

	altered_node = check_for_variable_existance(cmd, env);
	if (altered_node && (ft_strlen(altered_node->content) == ft_strlen(cmd)))
	{
		altered_node->content = ft_strdup(cmd);
	}
	else if (altered_node
		&& (ft_strlen(altered_node->content) != ft_strlen(cmd)))
		return ;
	else
		ft_lstadd_back(&env, ft_lstnew(strdup(cmd)));
}
