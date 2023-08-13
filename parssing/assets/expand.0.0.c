/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.0.0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:58:08 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 19:14:07 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

static char	*extraction(char *buffer, char **env)
{
	char	*variable;

	variable = _getenv(buffer, env);
	return (variable);
}

static char	*create_buffer(char *c, char *s, char *d, int doc)
{
	char	*buffer;

	buffer = NULL;
	if (*s == 0 && (*c == '\'') && *d == 0)
		*s = *c;
	else if (*c == *s)
		*s = 0;
	if (*d == 0 && (*c == '\"') && *s == 0)
		*d = *c;
	else if (*c == *d)
		*d = 0;
	else if (*c == '$' && ((*s == 0 && *d == 0) || doc))
		buffer = bufferin(c);
	else if (*c == '$' && (*d != 0 || doc))
		buffer = _bufferin(c);
	return (buffer);
}

static t_expand	init(void)
{
	t_expand	expand;

	expand.string = NULL;
	expand.buffer = NULL;
	expand.variable = NULL;
	expand.i = 0;
	expand.s = 0;
	expand.d = 0;
	expand.len = 0;
	return (expand);
}

static char	*startex(char *input, t_expand e, char **env, int doc)
{
	while (input && input[e.i])
	{
		e.buffer = create_buffer(&(input[e.i]), &(e.s), &(e.d), doc);
		if (e.buffer)
		{
			e.j = 0;
			e.variable = extraction(e.buffer, env);
			if (!e.variable[0])
				e.string = re_alloc(e.string, e.variable[0], e.len);
			while (e.variable[e.j])
				e.string = re_alloc(e.string, e.variable[e.j++], e.len++);
			free(e.variable);
			e.i += ft_strlen(e.buffer);
			free(e.buffer);
		}
		else
			e.string = re_alloc(e.string, input[e.i], e.len++);
		e.i++;
	}
	return (e.string);
}

char	*expand(char *input, char **env, int doc)
{
	char		*output;
	t_expand	expand;

	expand = init();
	output = startex(input, expand, env, doc);
	return (output);
}
