/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.0.1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:59:13 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 14:07:03 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

char	*_getenv(char *buffer, char **env)
{
	int			i;
	size_t		len;

	i = 0;
	len = ft_strlen(buffer);
	if (!ft_strncmp(buffer, "?", 1))
		return (ft_itoa(g_glob.exit_status));
	if (!ft_strncmp(buffer, "$", 1))
		return (ft_strdup("$$"));
	while (env && env[i])
	{
		if (ft_strncmp(buffer, env[i], len) == 0
			&& (env[i])[len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (ft_strdup("\0"));
}

int	end_del(char ch)
{
	int		i;
	char	*special_char;

	i = 0;
	special_char = " \t\n\f\v\r\b\"\'\\`~!@#$%^&*()-=+[]{};?:/.>|,<\0";
	while (special_char[i])
	{
		if (special_char[i] == ch)
			return (0);
		i++;
	}
	return (1);
}

int	stay(char ch)
{
	int		i;
	char	*special_char;

	i = 0;
	special_char = " \t\n\f\v\r\b\\~#%^&()-=+[]{};:/.>|,<";
	while (special_char[i])
	{
		if (special_char[i] == ch)
			return (0);
		i++;
	}
	return (1);
}

int	start_del_ex(char ch)
{
	int		i;
	char	*special_char;

	i = 0;
	special_char = "$`!?@0123456789";
	while (special_char[i])
	{
		if (special_char[i] == ch)
			return (0);
		i++;
	}
	return (1);
}

char	*re_alloc(char *input, char c, int len)
{
	char	*tmp;

	tmp = NULL;
	tmp = malloc(len + 2);
	if (input != NULL)
	{
		ft_memmove(tmp, input, len);
		free(input);
		input = NULL;
	}
	input = tmp;
	input[len] = c;
	input[len + 1] = 0;
	return (input);
}
