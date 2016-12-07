/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:47:38 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/07 20:23:54 by eduwer           ###   ########.fr       */
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
	iter_max = 100;
	while (i < iter_max)
	{
		result = cpow(result, 2.0) + nb;
		if (cabs(result) > 2)
			break;
		i++;
	}
	if (i == iter_max)
		mlx_pixel_put(infos->mlx, infos->win, infos->pt_x, infos->pt_y, 0xFFFFFF);
}

int		mandelbrot(t_win *infos)
{
	double complex nb;
	double x_to_add;
	double y_to_add;

	nb = -2.0 + 1 * I;
	x_to_add = (double)3.0 / (double)1500.0;
	y_to_add = (double)2.0 / (double)1000.0;
	infos->win = mlx_new_window(infos->mlx, 1500, 1000, "mandelbrot");
	infos->pt_y = 0;
	while (infos->pt_y < 1000)
	{
		infos->pt_x = 0;
		while (infos->pt_x < 1500)
		{
			calc_mandelbrot(nb, infos);
			nb += x_to_add;
			(infos->pt_x)++;
		}
		nb = -2.0 + (cimag(nb) - y_to_add) * I;
		(infos->pt_y)++;
	}
	printf ("fin mandelbrot\n");
	return (1);
}
