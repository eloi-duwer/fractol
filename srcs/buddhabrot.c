/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:47:38 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/14 14:30:03 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	find_coords(t_complex result, t_win *infos, int tab[1000][1500])
{
	int	x;
	int	y;

	x = nearbyint((result.real_part + 2) / infos->x_to_add);
	y = nearbyint((1 - result.imag_part) / infos->y_to_add);
	if (x < 1500 && y < 1000 && x >= 0 && y >= 0)
		tab[y][x] += 0x0F0F0F;
}

void	make_buddha(t_complex *nb, t_win *infos, int tab[1000][1500])
{
	t_complex	result;
	int			i;
	int			iter_max;
	double		mem_real_part;

	result.real_part = 0;
	result.imag_part = 0;
	i = 0;
	iter_max = infos->iter_max;
	while (i < iter_max && pow2(result.real_part) + pow2(result.imag_part) <= 4)
	{
		mem_real_part = result.real_part;
		result.real_part = pow2(result.real_part) \
			- pow2(result.imag_part) + nb->real_part;
		result.imag_part = 2 * mem_real_part * result.imag_part \
			+ nb->imag_part;
		find_coords(result, infos, tab);
		i++;
	}
}

void	calc_mandelbrot_buddha(t_complex *nb, int color_tab[1000][1500], \
								t_win *infos)
{
	t_complex		result;
	int				i;
	int				iter_max;
	double			mem_real_part;

	result.real_part = 0;
	result.imag_part = 0;
	i = 0;
	iter_max = infos->iter_max;
	while (i < iter_max && pow2(result.real_part) + pow2(result.imag_part) <= 4)
	{
		mem_real_part = result.real_part;
		result.real_part = pow2(result.real_part) \
			- pow2(result.imag_part) + nb->real_part;
		result.imag_part = 2 * mem_real_part * result.imag_part \
			+ nb->imag_part;
		i++;
	}
	if (i > 50 && i < iter_max)
		make_buddha(nb, infos, color_tab);
}

void	mandelbrot_buddha(t_win *infos, int color_tab[1000][1500], \
							char *mem_img)
{
	t_complex	nb;
	int			i;
	int			j;

	nb.imag_part = 1;
	while (nb.imag_part > -1)
	{
		nb.real_part = -2;
		while (nb.real_part < 1)
		{
			calc_mandelbrot_buddha(&nb, color_tab, infos);
			nb.real_part += infos->x_to_add;
		}
		nb.imag_part -= infos->y_to_add;
	}
	i = 0;
	while (i < 1500 && ((j = 0) == 0))
	{
		while (j < 1000)
		{
			put_pixel_on_image(mem_img, color_tab[j++][i]);
			mem_img += 4;
		}
		i++;
	}
}

void	init_buddhabrot(t_win *info)
{
	int		tab_color[1000][1500];
	int		i;
	int		j;
	char	*mem_img;

	i = 0;
	while (i < 1000)
	{
		j = 0;
		while (j < 1500)
			tab_color[i][j++] = 0;
		i++;
	}
	info->iter_max = 500;
	info->img = mlx_new_image(info->mlx, 1000, 1500);
	info->pt_img = mlx_get_data_addr(info->img, &(info->bits_per_pixel), \
			&(info->size_line), &(info->endian));
	info->x_to_add = (double)3 / (double)1500;
	info->y_to_add = (double)2 / (double)1000;
	mem_img = info->pt_img;
	mandelbrot_buddha(info, tab_color, mem_img);
	info->win = mlx_new_window(info->mlx, 1000, 1300, "buddhabrot");
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, -200);
}
