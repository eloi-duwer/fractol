/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:37:04 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/13 18:37:11 by eduwer           ###   ########.fr       */
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
	proportion_y = 1 - ((double)y / 1000);
	size_x = infos->x_max - infos->x_min;
	size_y = infos->y_max - infos->y_min;
	infos->x_min += (0.1 * size_x) * proportion_x;
	infos->x_max = infos->x_min + (size_x * 0.9);
	infos->y_min += (0.1 * size_y) * proportion_y;
	infos->y_max = infos->y_min + (size_y * 0.9);
	exec_and_draw(infos);
}

void	dezoom(int x, int y, t_win *infos)
{
	double proportion_x;
	double proportion_y;
	double size_x;
	double size_y;

	proportion_x = (double)x / 1500;
	proportion_y = 1 - ((double)y / 1000);
	size_x = infos->x_max - infos->x_min;
	size_y = infos->y_max - infos->y_min;
	infos->x_min -= (0.1 * size_x) * proportion_x;
	infos->x_max = infos->x_min + (size_x * 1.1);
	infos->y_min -= (0.1 * size_y) * proportion_y;
	infos->y_max = infos->y_min + (size_y * 1.1);
	exec_and_draw(infos);
}

double	pow2(double nb)
{
	return (nb * nb);
}

int		motion_mouse(int x, int y, void *param)
{
	if (((t_win *)param)->fix == 0)
	{
		((t_win *)param)->base_nb_real = ((t_win *)param)->x_min + \
			((t_win *)param)->x_to_add * x;
		((t_win *)param)->base_nb_imag = -(((t_win *)param)->y_min + \
			((t_win *)param)->y_to_add * y);
		printf("parameter %f %+fi,\n x = %d, y = %d\n", \
			((t_win *)param)->base_nb_real, ((t_win *)param)->base_nb_imag, x, y);
	exec_and_draw((t_win *)param);
	}
	return (1);
}
