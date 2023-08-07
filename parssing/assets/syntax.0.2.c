/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxExtra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:44:16 by yachaab           #+#    #+#             */
/*   Updated: 2023/06/14 15:44:32 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

void	*white_space_only(char *input)
{
	while (input && ((*input >= 9 && *input <= 13) || *input == 32))
		input++;
	if (*input == '\0')
		return (NULL);
	else
		return ("OK");
}
