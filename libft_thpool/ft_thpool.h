/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thpool.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 18:39:20 by nkamolba          #+#    #+#             */
/*   Updated: 2017/12/17 23:13:16 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_THPOOL_H
# define FT_THPOOL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <pthread.h>

typedef struct				s_tp_thread
{
	struct s_task_queue		*task_queue;
	struct s_data_queue		*data_queue;
	pthread_mutex_t			mutex;
	pthread_cond_t			cond_signal;
	pthread_t				*tid;
	int						len;
	int						close_thread;
}							t_tp_thread;

typedef struct				s_data_queue
{
	struct s_data			*first;
	struct s_data			*last;
}							t_data_queue;

typedef struct				s_data
{
	char					*str;
	struct s_data			*next;
}							t_data;

typedef struct				s_task
{
	void					(*f)(t_data *);
	struct s_data			*data;
	struct s_task			*next;
}							t_task;

typedef struct				s_task_queue
{
	struct s_task			*first;
	struct s_task			*last;
}							t_task_queue;

t_tp_thread					*tp_create(int num);
void						*thread_task(void *arg);
void						tp_exec_queue_add(t_tp_thread *tp,
								void (*f)(t_data *), t_data *data);
void						tp_wait_for_queue(t_tp_thread *tp);

t_data_queue				*create_data_queue(void);
t_data						*create_data(char *str);
void						enqueue_data(t_data_queue *queue, t_data *node);
char						*dequeue_data(t_data_queue *queue);
void						delete_queue(t_data_queue *queue);

t_task_queue				*create_task_queue(void);
t_task						*create_task(void (*f)(t_data *), t_data *data);
void						enqueue_task(t_task_queue *task_queue,
								t_task *task);
t_task						*dequeue_task(t_task_queue *task_queue);
void						delete_task_queue(t_task_queue *task_queue);

t_tp_thread					*g_tp;

#endif
