/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_task.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:56:41 by nkamolba          #+#    #+#             */
/*   Updated: 2017/12/17 23:14:30 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_thpool.h"

t_task_queue	*create_task_queue(void)
{
	t_task_queue	*task_queue;

	if (!(task_queue = (t_task_queue *)malloc(sizeof(t_task_queue))))
		return (NULL);
	task_queue->first = NULL;
	task_queue->last = NULL;
	return (task_queue);
}

t_task			*create_task(void (*f)(t_data *), t_data *data)
{
	t_task	*task;

	if (!(task = (t_task *)malloc(sizeof(t_task))))
		return (NULL);
	task->data = data;
	task->f = f;
	task->next = NULL;
	return (task);
}

void			enqueue_task(t_task_queue *task_queue, t_task *task)
{
	if (!task_queue || !task)
		return ;
	if (task_queue->first == NULL)
	{
		task_queue->first = task;
		task_queue->last = task;
	}
	else
	{
		task_queue->last->next = task;
		task_queue->last = task;
	}
}

t_task			*dequeue_task(t_task_queue *task_queue)
{
	t_task	*task;

	if (!task_queue)
		return (NULL);
	task = task_queue->first;
	if (task_queue->first == task_queue->last)
	{
		task_queue->first = NULL;
		task_queue->last = NULL;
	}
	else
		task_queue->first = task_queue->first->next;
	return (task);
}

void			delete_task_queue(t_task_queue *task_queue)
{
	t_task	*task;
	t_task	*temp;

	if (!task_queue)
		return ;
	task = task_queue->first;
	while (task)
	{
		temp = task->next;
		free(task);
		task = temp;
	}
	free(task_queue);
}
