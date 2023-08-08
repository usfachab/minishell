/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:12 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/08 18:27:55 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	is_limiter(char *str, char *arg)
{
	int	str_len;
	int	arg_len;

	str_len = ft_strlen(str);
	arg_len = ft_strlen(arg);
	if ((str_len == arg_len && ft_strncmp(str, arg, arg_len) == 0))
		return (1);
	return (0);
}
