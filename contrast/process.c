/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:18:15 by nkamolba          #+#    #+#             */
/*   Updated: 2017/12/17 23:09:32 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_contrast.h"

void	usage(void)
{
	ft_putstr(".\\ft_contrast -f src_file.pgm -c contrast -o dest_file.pgm\n");
	exit(0);
}

void	read_argument(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'f')
				g_in_fd = open(argv[i + 1], O_RDONLY);
			if (argv[i][1] == 'o')
				g_out_fd = open(argv[i + 1], O_WRONLY | O_CREAT, 0775);
			if (argv[i][1] == 'c')
				g_contrast = ft_atoi(argv[i + 1]);
		}
		i++;
	}
	if (!g_in_fd || !g_contrast || !g_out_fd)
		usage();
}

void	copy_image_header(void)
{
	char	buff[33];
	int		read_result;
	int		new_line;
	int		len;

	read_result = read(g_in_fd, buff, 32);
	buff[read_result] = '\0';
	new_line = 0;
	len = 0;
	while (new_line < 3)
	{
		ft_putchar_fd(buff[len], g_out_fd);
		if (buff[len++] == '\n')
			new_line++;
	}
	lseek(g_in_fd, len - 32, SEEK_CUR);
}

t_data	*read_input(char *buff, int read_result)
{
	int			i;
	char		*str;
	t_data		*data;

	buff[read_result] = 0;
	i = 1;
	while (ft_isdigit(buff[read_result - i]))
	{
		lseek(g_in_fd, -1, SEEK_CUR);
		i++;
	}
	buff[read_result - i + 1] = '\0';
	if (!(str = ft_strnew(read_result)))
		return (NULL);
	ft_strcpy(str, buff);
	if (!(data = create_data(str)))
		return (NULL);
	return (data);
}

void	write_output(t_tp_thread *tp)
{
	char	*str;

	while (tp->data_queue->first)
	{
		str = dequeue_data(tp->data_queue);
		ft_putstr_fd(str, g_out_fd);
	}
}
