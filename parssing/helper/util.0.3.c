/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util0.3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:29:40 by yachaab           #+#    #+#             */
/*   Updated: 2023/07/30 23:37:28 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lib.h"

void	*ft_lstlast_subnode(t_file *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	*ft_lstlast_node(t_data *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

t_file	*ft_lstnew_subnode(char *content, int type)
{
	t_file	*node;

	node = NULL;
	node = (t_file *)malloc(sizeof(t_file));
	if (!node)
		return (NULL);
	node->file_name = content;
	node->type = type;
	node->next = NULL;
	return (node);
}

t_data	*ft_lstnew_node(char **command, t_file *files)
{
	t_data	*node;

	node = NULL;
	node = (t_data *)malloc(sizeof(t_data));
	if (!node)
		return (NULL);
	node->cmd_args = command;
	node->file = files;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back_subnode(t_file **lst, t_file *new)
{
	t_file	*last;

	last = NULL;
	if (!lst || !new)
		return ;
	last = ft_lstlast_subnode(*lst);
	if (last == NULL)
		*lst = new;
	else
		last->next = new;
}
