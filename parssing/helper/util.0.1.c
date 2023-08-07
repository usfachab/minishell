/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.0.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:27:57 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/02 16:19:47 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (s1[i])
		i++;
	ptr = malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!d && !s)
		return (0);
	if (d < s)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	if (d > s)
	{
		i = len;
		while (i--)
			d[i] = s[i];
	}
	return ((void *)d);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	char	*bigo;

	i = 0;
	if (!big)
		return (NULL);
	bigo = (char *)big;
	if (little[i] == '\0')
		return (bigo);
	while (i < len && bigo[i])
	{
		j = 0;
		while ((bigo[i + j] == little[j]) && (i + j) < len)
		{
			if (little[j + 1] == '\0' )
				return (bigo + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*_join_path(char *path, char *cmd)
{
	size_t		i;
	size_t		j;
	char		*ptr;

	i = 0;
	ptr = malloc(ft_strlen(path) + ft_strlen(cmd) + 2);
	if (!ptr)
		return (NULL);
	while (i < ft_strlen(path))
	{
		ptr[i] = path[i];
		i++;
	}
	ptr[i] = '/';
	i += 1;
	ptr[i] = 0;
	j = 0;
	while (j < ft_strlen(cmd))
	{
		ptr[i + j] = cmd[j];
		j++;
	}
	ptr[i + j] = 0;
	return (ptr);
}
