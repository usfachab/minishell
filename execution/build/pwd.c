/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selrhair <selrhair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:51:34 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/15 15:51:54 by selrhair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	_pwd(void)
{
	t_list	*temp;
	char	*str;
	char	*content;

	temp = g_glob.env;
	str = getcwd(NULL, 0);
	if (!str)
	{
		content = node_content(temp, "PWD");
		if (content && content[4])
			printf("%s\n", content + 4);
	}
	else
	{
		printf("%s\n", str);
		free(str);
	}
}
