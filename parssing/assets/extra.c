/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:41:46 by yachaab           #+#    #+#             */
/*   Updated: 2023/07/29 00:35:36 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

void	lexer_skip_white_space(t_lexer *lexer)
{
	while ((lexer->c >= 9 && lexer->c <= 13) || lexer->c == 32)
		lexer_advence(lexer);
}

int	_white_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_special_character(char ch)
{
	char	*special_char;

	special_char = " \t\n\f\v\r\b\"\'\\`~!@#$%^&*()_-=+[]{};:/?.>,<";
	if (ft_strchr(special_char, ch))
		return (1);
	return (0);
}

char	*add_quote_to_variable(char *value)
{
	int		i;
	int		valen;
	char	*new_val;

	if (!value)
		return (NULL);
	i = 0;
	valen = ft_strlen(value);
	new_val = malloc(sizeof(char) * (valen + 3));
	if (!new_val)
		internal_error_msg("", ENOMEM);
	new_val[i] = '\"';
	while (value[i])
	{
		if (value[i] == 32)
			new_val[i + 1] = -42;
		else
			new_val[i + 1] = value[i];
		i++;
	}
	new_val[i + 1] = '\"';
	new_val[i + 2] = '\0';
	return (new_val);
}

int	variable_contain_white_space(char *variable)
{
	int	i;

	i = 0;
	while (variable && _white_space(variable[i]))
		i++;
	while (variable && variable[i])
	{
		if (_white_space(variable[i])
			&& !_white_space(variable[i + 1]) && variable[i + 1] != 0)
			return (1);
		i++;
	}
	return (0);
}
