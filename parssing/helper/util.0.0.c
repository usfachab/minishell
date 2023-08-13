/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.0.0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:26:15 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 12:47:07 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

void	internal_error_msg(char *str, unsigned int err)
{
	write(2, "minishell: ", 11);
	perror(str);
	g_glob.exit_status = err;
	exit(err);
}

void	external_error_msg(char *str, unsigned int err)
{
	write(2, str, ft_strlen(str));
	g_glob.exit_status = err;
	exit(err);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		if (!s1[i] || !s2[i])
			break ;
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s && s[i])
		i++;
	return (i);
}
