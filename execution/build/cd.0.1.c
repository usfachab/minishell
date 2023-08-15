/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.0.1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:54:44 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:50:22 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

char	*node_content(t_list *e, char *arg)
{
	char	*envkey;
	char	*equal;

	if (!e || !(e->content))
		return (0);
	while (e)
	{
		envkey = ft_strdup(e->content);
		equal = ft_strchr(envkey, '=');
		if (equal)
			envkey[equal - envkey] = 0;
		if (!ft_strcmp(envkey, arg))
		{
			free(envkey);
			envkey = NULL;
			return (e->content);
		}
		free(envkey);
		envkey = NULL;
		e = e->next;
	}
	return (NULL);
}

void	set_pwd(char *arg, char *var)
{
	char	*envkey;
	t_list	*e;
	char	*key;

	e = g_glob.env;
	key = ft_strjoin(arg, "=");
	while (e)
	{
		envkey = ft_strdup(e->content);
		if (ft_strchr(envkey, '='))
			envkey[ft_strchr(envkey, '=') - envkey] = 0;
		if (!ft_strcmp(envkey, arg))
		{
			free(envkey);
			free(e->content);
			e->content = ft_strjoin(key, var);
			free(key);
			return ;
		}
		free(envkey);
		envkey = NULL;
		e = e->next;
	}
	ft_lstadd_back(&(g_glob.env), ft_lstnew(ft_strjoin(key, var)));
	free(key);
}
