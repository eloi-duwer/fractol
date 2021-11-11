/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:47:38 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/14 17:31:35 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

double	calc_mandelbrot(t_complex *nb, char *pt_img, t_win *infos)
{
	t_complex		result;
	int				i;
	int				iter_max;

	result.real_part = infos->base_nb_real;
	result.imag_part = infos->base_nb_imag;
	i = 0;
	iter_max = infos->iter_max;
	while (i < iter_max && pow2(result.real_part) + pow2(result.imag_part) <= 4)
	{
		mandel_julia_power(nb, &result, infos);
		i++;
	}
	calc_color(i - 1, iter_max - 1, pt_img);
	return (infos->x_to_add);
}

void	*calc_100_lines(void *inf)
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
		while (x++ < ((t_win *)inf)->pixels_x)
		{
			nb.real_part += calc_mandelbrot(&nb, pt_img, (t_win *)inf);
			pt_img += 4;
		}
		nb.real_part = ((t_win *)inf)->x_min;
		nb.imag_part = nb.imag_part - (((t_win *)inf)->y_to_add * 10);
		pt_img += 9 * ((t_win *)inf)->size_line;
	}
	return (NULL);
}

void	mandelbrot(t_win *infos)
{
	int			nb_threads;
	int			i;
	pthread_t	threads[10];

	infos->x_to_add = (infos->x_max - infos->x_min) / (double)infos->pixels_x;
	infos->y_to_add = (infos->y_max - infos->y_min) / (double)infos->pixels_y;
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

void	init_mandelbrot2(t_win *infos)
{
	if (infos->power == 2)
	{
		infos->x_min = -2;
		infos->x_max = 1;
		infos->y_min = -1;
		infos->y_max = 1;
		infos->iter_max = 50;
		infos->fix = 1;
		infos->base_nb_real = 0;
		infos->base_nb_imag = 0;
		infos->pixels_x = 1500;
		infos->pixels_y = 1000;
		infos->img = mlx_new_image(infos->mlx, 1500, 1000);
		infos->pt_img = mlx_get_data_addr(infos->img, \
			&(infos->bits_per_pixel), &(infos->size_line), &(infos->endian));
	}
	else
		init_mandel_julia_power(infos);
	mandelbrot(infos);
}

void	init_mandelbrot(t_win *infos)
{
	write(1, "controls : arrows to move,\n", 27);
	write(1, "+ to increase the number of iterations,\n", 40);
	write(1, "- to decrease the number of iterations,\n", 40);
	write(1, "F to fix/unfix the Mandelbrot parameter,\n", 41);
	write(1, "scroll the mouse to zoom/dezoom,\n", 33);
	write(1, "move the mouse to change the Mandelbrot parameter,\n", 51);
	write(1, "esc to quit.\n", 13);
	write(1, "Press enter to continue\n", 24);
	while (getchar() != '\n')
	{
	}
	pthread_mutex_init(&(infos->mutex_y), NULL);
	init_mandelbrot2(infos);
	infos->win = mlx_new_window(infos->mlx, infos->pixels_x, \
		infos->pixels_y, "mandelbrot");
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img, 0, 0);
}
