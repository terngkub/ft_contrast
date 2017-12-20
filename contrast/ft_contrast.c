/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:24:11 by nkamolba          #+#    #+#             */
/*   Updated: 2017/12/17 23:08:30 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_contrast.h"

static void	itoa_str(int num, char *ret, int *i)
{
	if (num >= 100)
	{
		ret[*i] = num / 100 + '0';
		*i += 1;
	}
	if (num >= 10)
	{
		ret[*i] = (num / 10) % 10 + '0';
		*i += 1;
	}
	ret[*i] = num % 10 + '0';
	*i += 1;
}

void		ft_contrast(t_data *data)
{
	char	*str;
	char	*ret;
	int		num;
	int		i;

	str = data->str;
	if (!(ret = ft_strnew(ft_strlen(str))))
		return ;
	i = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			num = 0;
			while (ft_isdigit(*str))
				num = (num * 10) + (*str++ - '0');
			num = num * g_contrast / 100;
			itoa_str(num, ret, &i);
		}
		else
			ret[i++] = *str++;
	}
	ret[i] = '\0';
	data->str = ret;
}
