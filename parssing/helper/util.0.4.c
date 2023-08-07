/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.0.4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:30:38 by yachaab           #+#    #+#             */
/*   Updated: 2023/07/30 23:37:02 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

void	ft_lstadd_back_node(t_data **lst, t_data *new)
{
	t_data	*last;

	last = NULL;
	if (!lst || !new)
		return ;
	last = ft_lstlast_node(*lst);
	if (last == NULL)
		*lst = new;
	else
		last->next = new;
}

size_t	ft_strlen_x(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*_join(char *path, char *cmd)
{
	size_t		i;
	size_t		j;
	char		*ptr;

	i = 0;
	ptr = malloc(ft_strlen_x(path) + ft_strlen_x(cmd) + 2);
	if (!ptr)
		return (NULL);
	while (i < ft_strlen_x(path))
	{
		ptr[i] = path[i];
		i++;
	}
	ptr[i] = 0;
	free(path);
	j = 0;
	while (j < ft_strlen_x(cmd))
	{
		ptr[i + j] = cmd[j];
		j++;
	}
	ptr[i + j] = ' ';
	ptr[i + j + 1] = 0;
	return (ptr);
}

t_list	*ft_fill_list(char **line)
{
	int		i;
	t_list	*list;

	i = 0;
	list = ft_lstnew(line[0]);
	while (line[++i])
		ft_lstadd_back(&list, ft_lstnew(line[i]));
	return (list);
}

void	ft_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->content && ft_strchr(tmp->content, '='))
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
