/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertToArray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:25:48 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/12 22:42:23 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static char	*find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static char	**splitpath(void)
{
	char	**splited_path;
	char	*path;

	path = find_path(g_glob.envp);
	if (!path)
		return (NULL);
	splited_path = split(path, ":\0");
	return (splited_path);
}

void	convert_to_array_help(void)
{
	if (g_glob.envp)
	{
		free(g_glob.envp);
		g_glob.envp = NULL;
	}
}

void	convert_to_array(void)
{
	t_list			*lst;
	int				i;

	lst = g_glob.env;
	convert_to_array_help();
	g_glob.envp = malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	i = 0;
	while (lst)
	{
		g_glob.envp[i] = lst->content;
		i++;
		lst = lst->next;
	}
	g_glob.envp[i] = NULL;
	i = 0;
	while (g_glob.splited_path && g_glob.splited_path[i])
	{
		free(g_glob.splited_path[i]);
		i++;
	}
	if (g_glob.splited_path)
		free(g_glob.splited_path);
	g_glob.splited_path = splitpath();
}
