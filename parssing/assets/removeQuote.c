/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removeQuote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:51:39 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 18:42:54 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

char	*remove_quote(char *value)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	c = 0;
	while (value[i])
	{
		if (c == 0 && (value[i] == '\'' || value[i] == '\"'))
			c = value[i];
		else if (value[i] == c)
			c = 0;
		else
			value[j++] = value[i];
		i++;
	}
	value[j] = 0;
	return (value);
}

void	init_var_with_env_variable(char **env)
{
	int	i;

	i = 0;
	g_glob.env = NULL;
	g_glob.splited_path = NULL;
	while (env && env[i])
	{
		if (ft_strncmp("OLDPWD=", env[i], 7) && ft_strncmp("OLDPWD", env[i], 7))
			ft_lstadd_back(&(g_glob.env), ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	ft_lstadd_back(&(g_glob.env), ft_lstnew(ft_strdup("OLDPWD")));
	convert_to_array();
}
