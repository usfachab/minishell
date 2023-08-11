/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.0.3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:12:53 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/10 15:16:29 by yachaab          ###   ########.fr       */
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
	char	*equale;

	cmd = &(*(cmd + 1));
	equale = strchr(cmd, '=');
	while (equale && cmd && cmd < equale)
	{
		if (!alphaunder(*cmd) && (!((*cmd >= 48 && *cmd <= 57) || *cmd == '+')))
			return (0);
		cmd++;
	}
	return (1);
}
