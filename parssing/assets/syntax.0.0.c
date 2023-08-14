/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.0.0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:38:06 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/12 22:35:08 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

void	*search_for_identifier_form_front(char *input, char id)
{
	input = skip_white_space(input);
	if (input && *input == id)
	{
		printf("syntax error near to token %c\n", id);
		return (NULL);
	}
	return ("OK");
}

void	*search_for_identifier_form_back(char *input, char id)
{
	int	len;

	if (!input || !(*input))
		return (NULL);
	len = ft_strlen(input) - 1;
	while (((input[len] >= 9 && input[len] <= 13)
			|| input[len] == 32) && len > 0)
		len--;
	if (input[len] == id)
	{
		printf("syntax error near to token %c\n", id);
		return (NULL);
	}
	return ("OK");
}

void	*double_identifier(char *input, char id)
{
	while (input && *input)
	{
		if (*input == id)
		{
			input++;
			if (!search_for_identifier_form_front(input, id))
				return (NULL);
		}
		input++;
	}
	return ("OK");
}

void	*pipe_err(char *input)
{
	if (!search_for_identifier_form_front(input, '|'))
		return (NULL);
	if (!search_for_identifier_form_back(input, '|'))
		return (NULL);
	if (!double_identifier(input, '|'))
		return (NULL);
	return ("OK");
}

void	*syntax_err(char *input)
{
	find_char_and_replace_with_unprintable(input);
	if (!unclosed_quote(input))
	{
		g_glob.exit_status = 258;
		return (NULL);
	}
	if (!pipe_err(input))
	{
		g_glob.exit_status = 258;
		return (NULL);
	}
	if (!redirection_error(input))
	{
		g_glob.exit_status = 258;
		return (NULL);
	}
	if (!white_space_only(input))
		return (NULL);
	find_unprintable_and_replace_with_char(input);
	return ("OK");
}
