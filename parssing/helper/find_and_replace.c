/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:02:59 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/09 22:12:42 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

char	which_white_space(char ch)
{
	char	*found_char;
	char	*special_char;

	special_char = " \t\n\f\v\r";
	found_char = ft_strchr(special_char, ch);
	if (found_char)
		return (*found_char);
	return (0);
}

void	find_char_and_replace_with_unprintable(char *str)
{
	char	c;

	c = 0;
	while (str && *str)
	{
		if ((*str == '\'' || *str == '\"') && c == 0)
			c = *str;
		else if (*str == c)
			c = 0;
		else if (c != 0)
		{
			if (*str == '|')
				*str = -1;
			if (*str == '<')
				*str = -2;
			if (*str == '>')
				*str = -3;
			if (*str == which_white_space(*str))
				*str = -4;
		}
		str++;
	}
}

void	find_unprintable_and_replace_with_char(char *str)
{
	while (str && *str)
	{
		if (*str == -1)
			*str = '|';
		if (*str == -2)
			*str = '<';
		if (*str == -3)
			*str = '>';
		if (*str == -4)
			*str = ' ';
		str++;
	}
}

void	find_unprintable_replace_space(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == -1)
				str[i][j] = '|';
			if (str[i][j] == -2)
				str[i][j] = '<';
			if (str[i][j] == -3)
				str[i][j] = '>';
			if (str[i][j] == -4)
				str[i][j] = ' ';
			j++;
		}
		i++;
	}
}
