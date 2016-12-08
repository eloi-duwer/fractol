/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:47:38 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/08 17:15:02 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calc_mandelbrot(double complex nb, t_win *infos)
{
	double complex	result;
	int				i;
	int				iter_max;

	result = 0;
	i = 0;
	iter_max = 50;
	while (i < iter_max && cabs(result) <= 2)
	{
		result = cpow(result, 2.0) + nb;
		i++;
	}
	calc_color(i, iter_max, infos);
}

int		mandelbrot(t_win *infos)
{
	double complex nb;
	double x_to_add;
	double y_to_add;

	nb = -2.0 + 1 * I;
	x_to_add = 3.0 / 1500.0;
	y_to_add = 2.0 / 1000.0;
	infos->img = mlx_new_image(infos->mlx, 1500, 1000);
	infos->pt_img = mlx_get_data_addr(infos->img, &(infos->bits_per_pixel), \
			&(infos->size_line), &(infos->endian));
	infos->pt_y = 0;
	while (infos->pt_y < 1000)
	{
		infos->pt_x = 0;
		while (infos->pt_x < 1500)
		{
			calc_mandelbrot(nb, infos);
			nb += x_to_add;
			(infos->pt_x)++;
			(infos->pt_img) += 4;
		}
		nb = -2.0 + (cimag(nb) - y_to_add) * I;
		(infos->pt_y)++;
	}
	return (1);
}
