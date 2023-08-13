/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.0.2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:06:33 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 18:52:15 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

char	*collect_name(char *end)
{
	int	i;

	i = 0;
	while (end && end[i])
	{
		if (!end_del(end[i]))
		{
			end[i] = 0;
			break ;
		}
		i++;
	}
	return (end);
}

char	*_bufferin(char *input)
{
	char	*start;
	char	*end;

	start = input;
	end = ft_strdup(start + 1);
	if ((end[0] == '\'' || end[0] == '\"') || !stay(end[0]))
	{
		free(end);
		return (NULL);
	}
	else if (!start_del_ex(end[0]))
	{
		end[1] = 0;
		return (end);
	}
	else
		end = collect_name(end);
	return (end);
}

char	*bufferin(char *input)
{
	char	*end;

	end = NULL;
	end = ft_strdup(input + 1);
	if (end[0] == '\'' || end[0] == '\"')
	{
		free(end);
		return (strdup("\0"));
	}
	else if (!end[0] || !stay(end[0]))
	{
		free(end);
		return (NULL);
	}
	else if (!start_del_ex(end[0]))
	{
		end[1] = 0;
		return (end);
	}
	else
		end = collect_name(end);
	return (end);
}
