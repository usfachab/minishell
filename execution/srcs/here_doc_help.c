/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:12 by selrhair          #+#    #+#             */
/*   Updated: 2023/08/13 15:19:03 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int	is_limiter(char *str, char *arg)
{
	int	str_len;
	int	arg_len;

	str_len = ft_strlen(str);
	arg_len = ft_strlen(arg);
	if ((str_len == arg_len && ft_strncmp(str, arg, arg_len) == 0))
		return (1);
	return (0);
}

int	open_file_in_main_work(t_data *data, t_file *file)
{
	if (file->type == 2)
		data->in = open(file->file_name, O_RDONLY, 0644);
	else if (file->type == 3)
		data->out = open(file->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (file->type == 4)
		data->out = open(file->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (file->type == 5 || file->type == 6)
		data->in = data->last_hdc;
	else if (file->type == -1)
	{
		ambiguous_error(file);
		data->unopened_file = -1;
		return (0);
	}
	return (1);
}
