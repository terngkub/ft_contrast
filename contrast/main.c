/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:28:42 by nkamolba          #+#    #+#             */
/*   Updated: 2017/12/17 22:04:53 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_contrast.h"

int		main(int argc, char **argv)
{
	char		buff[BUFF_SIZE + 1];
	int			read_result;
	t_data		*data;

	read_argument(argc, argv);
	copy_image_header();
	g_tp = tp_create(4);
	while ((read_result = read(g_in_fd, buff, BUFF_SIZE)) > 0)
	{
		data = read_input(buff, read_result);
		tp_exec_queue_add(g_tp, &ft_contrast, data);
	}
	tp_wait_for_queue(g_tp);
	write_output(g_tp);
	close(g_in_fd);
	close(g_out_fd);
	return (0);
}
