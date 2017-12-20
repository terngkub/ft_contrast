/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 20:33:55 by nkamolba          #+#    #+#             */
/*   Updated: 2017/12/17 23:11:46 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_thpool.h"

t_data_queue	*create_data_queue(void)
{
	t_data_queue	*data_queue;

	if (!(data_queue = (t_data_queue *)malloc(sizeof(t_data_queue))))
		return (NULL);
	data_queue->first = NULL;
	data_queue->last = NULL;
	return (data_queue);
}

t_data			*create_data(char *str)
{
	t_data		*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->str = str;
	data->next = NULL;
	return (data);
}

void			enqueue_data(t_data_queue *data_queue, t_data *data)
{
	if (!data_queue || !data)
		return ;
	if (data_queue->first == NULL)
	{
		data_queue->first = data;
		data_queue->last = data;
	}
	else
	{
		data_queue->last->next = data;
		data_queue->last = data;
	}
}

char			*dequeue_data(t_data_queue *data_queue)
{
	char		*str;
	t_data		*data;

	if (!data_queue)
		return (NULL);
	str = data_queue->first->str;
	data = data_queue->first;
	if (data_queue->first == data_queue->last)
	{
		data_queue->first = NULL;
		data_queue->last = NULL;
	}
	else
		data_queue->first = data_queue->first->next;
	free(data);
	return (str);
}

void			delete_queue(t_data_queue *queue)
{
	t_data		*data;
	t_data		*temp;

	if (!queue)
		return ;
	data = queue->first;
	while (data)
	{
		temp = data->next;
		free(data);
		data = temp;
	}
	free(queue);
}
