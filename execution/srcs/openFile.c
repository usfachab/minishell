/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openFile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:30:57 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/09 18:53:16 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static void	count_heredoc(int type, int *count)
{
	if (type == 5 || type == 6)
	{
		(*count)++;
		if (*count > 16)
		{
			printf("minishel: maximum here-document count exceeded\n");
			g_glob.exit_status = 2;
			exit(2);
		}
	}
}

void	save_last_in_out(t_parser_var *var)
{
	t_data	*tmp;
	t_file	*file;
	int		count;

	count = 0;
	tmp = var->data;
	while (tmp)
	{
		tmp->last_in = NULL;
		tmp->last_out = NULL;
		file = tmp->file;
		while (file)
		{
			count_heredoc(file->type, &count);
			if (file->type == 2 || file->type == 5 || file->type == 6)
				tmp->last_in = file;
			else if (file->type == 3 || file->type == 4)
				tmp->last_out = file;
			file = file->next;
		}
		tmp = tmp->next;
	}
}

static void	main_work_help(t_data *data, t_file *file)
{
	if (data->last_in && (data->last_in != file && (file->type != 5
				&& file->type != 6)) && (file->type != 3 && file->type != 4))
		close(data->in);
	if (data->last_out && (data->last_out != file)
		&& (file->type == 3 && file->type == 4))
		close(data->out);
}

static int	main_work(t_data *data, t_file *file)
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
		return (0);
	}
	if (data->in == -1 || data->out == -1)
	{
		perror(file->file_name);
		if (data->in == -1)
			return (-1);
		data->in = 0;
		data->out = 1;
		return (0);
	}
	main_work_help(data, file);
	return (1);
}

int	open_file_loop(t_data *data)
{
	t_file	*file;
	int		i;

	data->out = 1;
	file = data->file;
	while (file)
	{
		i = main_work(data, file);
		if (!i)
		{
			g_glob.exit_status = 1;
			return (0);
		}
		if (i == -1)
		{
			g_glob.exit_status = 1;
			return (-1);
		}
		file = file->next;
	}
	return (1);
}
