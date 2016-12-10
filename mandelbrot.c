/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:47:38 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/10 20:27:09 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calc_mandelbrot(double complex nb, char *pt_img)
{
	double complex	result;
	int				i;
	int				iter_max;

	result = 0;
	i = 0;
	iter_max = 50;
	while (i < iter_max && cabs(result) <= 2)
	{
		result = cpow(result, 2) + nb;
		i++;
	}
	calc_color(i, iter_max, pt_img);
}

void	*calc_100_lines(void *inf)
{
	char			*pt_img;
	int				y;
	int				x;
	double complex	nb;

	pthread_mutex_lock(&(((t_win *)inf)->mutex_y));
	y = ((t_win *)inf)->pt_y;
	((t_win *)inf)->pt_y += 100;
	pthread_mutex_unlock(&(((t_win *)inf)->mutex_y));
	pt_img = ((t_win*)inf)->pt_img + (y * ((t_win *)inf)->size_line);
	nb = ((t_win *)inf)->x_min + (((t_win *)inf)->y_max \
			-(((t_win *)inf)->y_to_add * y)) * I;
	y = 100;
	while (y-- > 0)
	{
		x = 0;
		while (x++ < 1500)
		{
			calc_mandelbrot(nb, pt_img);
			nb += ((t_win *)inf)->x_to_add;
			pt_img += 4;
		}
		nb = ((t_win *)inf)->x_min + (cimag(nb) - ((t_win *)inf)->y_to_add) * I;
	}
	return (NULL);
}

void	mandelbrot(t_win *infos)
{
	int			nb_threads;
	int			i;
	pthread_t	threads[10];

	infos->x_to_add = (infos->x_max - infos->x_min) / 1500;
	infos->y_to_add = (infos->y_max - infos->y_min) / 1000;
	infos->pt_y = 0;
	nb_threads = 0;
	while (nb_threads < 10)
	{
		pthread_create(&(threads[nb_threads]), NULL, \
			calc_100_lines, (void *)infos);
		nb_threads++;
	}
	i = 0;
	while (i < 10)
		pthread_join(threads[i++], NULL);
}

int		init_mandelbrot(t_win *infos)
{
	infos->x_min = -2;
	infos->x_max = 1;
	infos->y_min = -1;
	infos->y_max = 1;
	infos->img = mlx_new_image(infos->mlx, 1500, 1000);
	infos->pt_img = mlx_get_data_addr(infos->img, &(infos->bits_per_pixel), \
			&(infos->size_line), &(infos->endian));
	mandelbrot(infos);
	return (1);
}
