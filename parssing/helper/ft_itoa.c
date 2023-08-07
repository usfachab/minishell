/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:02:23 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/02 18:50:04 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

char	*skip_white_space(char *input)
{
	while (input && ((*input >= 9 && *input <= 13) || *input == 32))
		input++;
	return (input);
}

static int	count_digit(int n)
{
	int			count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		count++;
	}
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_converter(int n, char *string, int length)
{
	int	index;

	index = 0;
	string[length] = '\0';
	if (n < 0)
	{
		string[index] = '-';
		n = n * -1;
		index++;
	}
	while (length-- > index)
	{
		string[length] = n % 10 + 48;
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*string;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	string = (char *)malloc(sizeof(char) * (count_digit(n) + 1));
	if (!string)
		return (NULL);
	ft_converter(n, string, count_digit(n));
	return (string);
}
