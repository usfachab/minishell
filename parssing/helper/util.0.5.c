/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.0.5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 00:41:55 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/12 21:54:41 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

int	ft_strncmp_2(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (NULL);
	p = (char *) malloc ((ft_strlen (s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (s1 && s1[j])
		p[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

int	special_character_should_stay(char ch)
{
	char	*special_char;

	special_char = " \t\n\f\v\r\b\\\"\'`~%^&$()-=+[]{};:/.>,<";
	if (ft_strchr(special_char, ch))
		return (1);
	return (0);
}

int	special_character_should_remove(char ch)
{
	char	*special_char;

	special_char = " \t\n\f\v\r\b\"\'\\`!@#*-=+[]{};:/.>,<0123456789";
	if (ft_strchr(special_char, ch))
		return (1);
	return (0);
}

int	special_character_at_end(char ch)
{
	char	*special_char;

	special_char = " \t\n\f\v\r\b\"\'\\`~!@#$%^&*()-=+[]{};?:/.>,<";
	if (ft_strchr(special_char, ch))
		return (1);
	return (0);
}
