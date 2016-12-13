/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:47:38 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/13 15:16:19 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	calc_julia(t_complex *nb, char *pt_img, t_win *infos)
{
	t_complex		result;
	int				i;
	int				iter_max;
	double			mem_real_part;

	result.real_part = nb->real_part;
	result.imag_part = nb->imag_part;
	i = 0;
	iter_max = infos->iter_max;
	while (i < iter_max && pow2(result.real_part) + pow2(result.imag_part) <= 4)
	{
		mem_real_part = result.real_part;
		result.real_part = pow2(result.real_part) \
			- pow2(result.imag_part) + infos->base_nb_real;
		result.imag_part = 2 * mem_real_part * result.imag_part \
			+ infos->base_nb_imag;
		i++;
	}
	calc_color(i, iter_max, pt_img);
	return (infos->x_to_add);
}

void	*calc_100_lines_julia(void *inf)
{
	char			*pt_img;
	int				y;
	int				x;
	t_complex		nb;

	pthread_mutex_lock(&(((t_win *)inf)->mutex_y));
	y = ((t_win *)inf)->pt_y;
	(((t_win *)inf)->pt_y)++;
	pthread_mutex_unlock(&(((t_win *)inf)->mutex_y));
	pt_img = ((t_win*)inf)->pt_img + (y * ((t_win *)inf)->size_line);
	nb.real_part = ((t_win *)inf)->x_min;
	nb.imag_part = (((t_win *)inf)->y_max - (((t_win *)inf)->y_to_add * y));
	y = 100;
	while (y-- > 0 && (x = 0) == 0)
	{
		while (x++ < 1500)
		{
			nb.real_part += calc_julia(&nb, pt_img, (t_win *)inf);
			pt_img += 4;
		}
		nb.real_part = ((t_win *)inf)->x_min;
		nb.imag_part = nb.imag_part - (((t_win *)inf)->y_to_add * 10);
		pt_img += 9 * ((t_win *)inf)->size_line;
	}
	return (NULL);
}

void	julia(t_win *infos)
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
			calc_100_lines_julia, (void *)infos);
		nb_threads++;
	}
	i = 0;
	while (i < 10)
		pthread_join(threads[i++], NULL);
}

void	init_julia2(t_win *infos)
{
	infos->x_min = -1.5;
	infos->x_max = 1.5;
	infos->y_min = -1;
	infos->y_max = 1;
	infos->iter_max = 50;
	infos->base_nb_real = 0;
	infos->base_nb_imag = 0;
	infos->fix = 0;
	julia(infos);
}

void	init_julia(t_win *infos)
{
	write(1, "controls : arrows to move,\n", 27);
	write(1, "+ to increase the number of iterations\n", 39);
	write(1, "- to decrease the number of iterations\n", 39);
	write(1, "F to fix/unfix the Julia parameter,\n", 36);
	write(1, "scroll the mouse to zoom/dezoom,\n", 33);
	write(1, "move the mouse to change the Julia parameter,\n", 46);
	write(1, "esc to quit.\n", 13);
	write(1, "Press enter to continue\n", 24);
	while (getchar() != '\n')
	{
	}
	pthread_mutex_init(&(infos->mutex_y), NULL);
	infos->img = mlx_new_image(infos->mlx, 1500, 1000);
	infos->pt_img = mlx_get_data_addr(infos->img, &(infos->bits_per_pixel), \
			&(infos->size_line), &(infos->endian));
	init_julia2(infos);
}
