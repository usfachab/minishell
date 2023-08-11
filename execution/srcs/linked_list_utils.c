/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:29:06 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/10 23:49:01 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	ft_lstdelone(t_list *lst, t_list *next)
{
	if (!lst)
		return ;
	free(lst->content);
	lst->next = next;
	free(lst);
}
