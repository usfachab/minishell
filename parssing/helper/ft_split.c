/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:18:38 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/13 13:39:32 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

char	**ft_free(char **word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		free(word[i]);
		i++;
	}
	free(word);
	return (NULL);
}

int	count_word(const char *string, char *delim)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		if (string[i] != delim[0] && string[i] != delim[1]
			&& (string[i + 1] == delim[0] || string[i + 1] == delim[1]
				|| string[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	*collect_string(char *str, char *del, int *i)
{
	int			len;
	char		*string;
	char		*tmp;

	len = 0;
	string = NULL;
	while (str[*i] == del[0] || str[*i] == del[1])
		*i += 1;
	while (str[*i] != del[0] && str[*i] != del[1] && str[*i] != '\0')
	{
		tmp = malloc(len + 2);
		if (!tmp)
			return (NULL);
		if (string != NULL)
		{
			ft_memmove(tmp, string, len);
			free(string);
		}
		string = tmp;
		string[len] = str[*i];
		string[len + 1] = '\0';
		len++;
		*i += 1;
	}
	return (string);
}

char	**split(char *str, char *del)
{
	int			i;
	int			index;
	char		**word;
	char		*string;
	int			count;

	count = count_word(str, del);
	string = NULL;
	index = 0;
	i = 0;
	word = malloc(sizeof(char *) * (count + 1));
	if (!word)
		return (NULL);
	while (index < count)
	{
		string = collect_string(str, del, &i);
		word[index] = remove_quote(string);
		if (word[index] == NULL)
			return (ft_free(word));
		index++;
	}
	word[index] = NULL;
	return (word);
}
