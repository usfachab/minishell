/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removeQuote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:51:39 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/02 23:43:49 by yachaab          ###   ########.fr       */
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

void	init_var_with_env_variable(t_parser_var	*var, char **env)
{
	int	i;

	i = 0;
	var->env = NULL;
	var->splited_path = NULL;
	while (env && env[i])
	{
		ft_lstadd_back(&(var->env), ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	convert_to_array(var);
}
