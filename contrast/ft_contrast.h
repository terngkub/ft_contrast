/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 20:15:20 by nkamolba          #+#    #+#             */
/*   Updated: 2017/12/17 23:09:05 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTRAST_H
# define FT_CONTRAST_H

# include "../libft_thpool/ft_thpool.h"

void	usage(void);
void	read_argument(int argc, char **argv);
void	copy_image_header(void);
t_data	*read_input(char *buff, int read_result);
void	write_output(t_tp_thread *tp);

void	ft_contrast(t_data *data);

int		g_in_fd;
int		g_out_fd;
int		g_contrast;

#endif
