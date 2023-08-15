/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.0.3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:12:53 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:51:44 by selrhair         ###   ########.fr       */
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
	char	*equal;
	int		size;
	char	*tmp;

	tmp = ft_strdup(cmd);
	equal = ft_strchr(tmp, '=');
	if (equal)
		tmp[equal - tmp] = 0;
	size = ft_strlen(tmp) - 1;
	while (size >= 0)
	{
		if (!alphaunder(tmp[size])
			&& (!((tmp[size] >= 48 && tmp[size] <= 57) || tmp[size] == '+')))
			return (0);
		size--;
	}
	free(tmp);
	return (1);
}
