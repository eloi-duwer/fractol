/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:37:04 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/11 00:41:10 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(int x, int y, t_win *infos)
{
	double	proportion_x;
	double	proportion_y;
	double	size_x;
	double	size_y;

	proportion_x = (double)x / 1500;
	proportion_y =  1 - ((double)y / 1000);
	printf ("x = %d, y = %d, propx = %f, propy = %f\n", x, y, proportion_x, proportion_y);
	size_x = infos->x_max - infos->x_min;
	size_y = infos->y_max - infos->y_min;
	infos->x_min += (0.1 * size_x) * proportion_x;
	infos->x_max = infos->x_min + (size_x * 0.9);
	infos->y_min += (0.1 * size_y) * proportion_y;
	infos->y_max = infos->y_min + (size_y * 0.9);
	mandelbrot(infos);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img, 0, 0);
}

void	dezoom(int x, int y, t_win *infos)
{
	infos->x_min = -2;
	infos->x_max = 1;
	infos->y_min = -1;
	infos->y_max = 1;
	x = 0;
	y = 0;
	mandelbrot(infos);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img, 0, 0);
}
