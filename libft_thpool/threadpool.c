/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadpool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 21:41:25 by nkamolba          #+#    #+#             */
/*   Updated: 2017/12/17 23:13:59 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_thpool.h"

t_tp_thread	*tp_create(int num)
{
	if (!(g_tp = (t_tp_thread *)malloc(sizeof(t_tp_thread))))
		exit(1);
	g_tp->data_queue = create_data_queue();
	g_tp->task_queue = create_task_queue();
	pthread_mutex_init(&(g_tp->mutex), NULL);
	pthread_cond_init(&(g_tp->cond_signal), NULL);
	if (!(g_tp->tid = (pthread_t *)malloc(sizeof(pthread_t) * num)))
		return (NULL);
	g_tp->len = 0;
	while (g_tp->len < num)
		pthread_create(&(g_tp->tid[g_tp->len++]), NULL, thread_task, NULL);
	g_tp->close_thread = 0;
	return (g_tp);
}

void		*thread_task(void *arg)
{
	t_task	*task;

	(void)arg;
	while (1)
	{
		pthread_mutex_lock(&(g_tp->mutex));
		pthread_cond_wait(&(g_tp->cond_signal), &(g_tp->mutex));
		if (g_tp->task_queue->first == NULL)
		{
			pthread_mutex_unlock(&(g_tp->mutex));
			g_tp->close_thread++;
			return (NULL);
		}
		task = dequeue_task(g_tp->task_queue);
		pthread_mutex_unlock(&(g_tp->mutex));
		task->f(task->data);
	}
	g_tp->close_thread++;
	return (NULL);
}

void		tp_exec_queue_add(t_tp_thread *tp, void (*f)(t_data *),
				t_data *data)
{
	enqueue_data(tp->data_queue, data);
	enqueue_task(tp->task_queue, create_task(f, data));
	pthread_cond_signal(&(tp->cond_signal));
}

void		tp_wait_for_queue(t_tp_thread *tp)
{
	int		i;

	while (tp->close_thread < tp->len)
		pthread_cond_signal(&(tp->cond_signal));
	i = 0;
	while (tp->tid[i])
		pthread_join(tp->tid[i++], NULL);
}
