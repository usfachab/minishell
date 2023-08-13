/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.0.3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:12:53 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/12 23:09:50 by yachaab          ###   ########.fr       */
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
	
	equal = ft_strchr(cmd, '=');
	if (equal)
		cmd[equal - cmd] = 0;
	size = ft_strlen(cmd) - 1;
	while (size > 0)
	{
		if (!alphaunder(cmd[size]) && (!((cmd[size] >= 48 && cmd[size] <= 57) || cmd[size] == '+')))
			return (0);
		size--;
	}
	return (1);
}
