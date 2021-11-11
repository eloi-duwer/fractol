/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_julia_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 14:34:45 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/14 17:33:11 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void		mandel_julia_power2(t_complex *nb, t_complex *result, \
			t_win *infos, double mem_real_part)
{
	if (infos->power == 4)
	{
		result->real_part = pow2(result->real_part) * (pow2(result->real_part) \
			- (6 * pow2(result->imag_part))) \
			+ ft_power(result->imag_part, 4) + nb->real_part;
		result->imag_part = ((4 * mem_real_part) * (pow2(mem_real_part) \
			* result->imag_part - ft_power(result->imag_part, 3)) + \
			nb->imag_part);
	}
	if (infos->power == 5)
	{
		result->real_part = ft_power(result->real_part, 5) - \
			10 * ft_power(result->real_part, 3) * pow2(result->imag_part) + \
			5 * result->real_part * ft_power(result->imag_part, 4) + \
			nb->real_part;
		result->imag_part = 5 * ft_power(mem_real_part, 4) * result->imag_part \
			- 10 * pow2(mem_real_part) * ft_power(result->imag_part, 3) + \
			ft_power(result->imag_part, 5) + nb->imag_part;
	}
}

void		mandel_julia_power(t_complex *nb, t_complex *result, t_win *infos)
{
	double			mem_real_part;

	mem_real_part = result->real_part;
	if (infos->power == 2)
	{
		result->real_part = pow2(result->real_part) \
				- pow2(result->imag_part) + nb->real_part;
		result->imag_part = 2 * mem_real_part * result->imag_part \
			+ nb->imag_part;
	}
	if (infos->power == 3)
	{
		result->real_part = result->real_part * (pow2(result->real_part) - \
			(3 * pow2(result->imag_part))) + nb->real_part;
		result->imag_part = result->imag_part * (3 * pow2(mem_real_part) - \
			pow2(result->imag_part)) + nb->imag_part;
	}
	if (infos->power >= 4)
		mandel_julia_power2(nb, result, infos, mem_real_part);
}

void		init_mandel_julia_power(t_win *infos)
{
	infos->x_min = -1.5;
	infos->x_max = 1.5;
	infos->y_min = -1.5;
	infos->y_max = 1.5;
	infos->pixels_x = 1000;
	infos->pixels_y = 1000;
	infos->iter_max = 50;
	infos->base_nb_real = 0;
	infos->base_nb_imag = 0;
	infos->img = mlx_new_image(infos->mlx, 1000, 1000);
	infos->pt_img = mlx_get_data_addr(infos->img, \
		&(infos->bits_per_pixel), &(infos->size_line), &(infos->endian));
	if (infos->prog == 0)
		infos->fix = 1;
	else
		infos->fix = 0;
}
