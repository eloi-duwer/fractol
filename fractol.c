/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:55:54 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/08 17:05:01 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		funct_escape(int keycode, void *param)
{
	if (keycode == 53)
	{
		mlx_destroy_window(((t_win *)param)->mlx, ((t_win *)param)->win);
		exit(1);
	}
	return (0);
}

void	put_pixel_on_image(t_win *infos, int color)
{
	int				i;
	unsigned char	*color_pt;
	char			*pt_img_pixel;

	color = mlx_get_color_value(infos->mlx, color);
	color_pt = (unsigned char *)&color;
	pt_img_pixel = infos->pt_img;
	i = 0;
	while (i < 3)
	{
		*pt_img_pixel = *color_pt;
		pt_img_pixel++;
		color_pt++;
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_win	infos;
	int		ret;

	infos.mlx = mlx_init();
	ret = 0;
	if (argc >= 2)
	{
		if (ft_strcmp(argv[1], "mandelbrot") == 0)
			ret = mandelbrot(&infos);
		if (ret == 1)
		{
			infos.win = mlx_new_window(infos.mlx, 1500, 1000, argv[1]);
			mlx_put_image_to_window(infos.mlx, infos.win, infos.img, 0, 0);
			mlx_key_hook(infos.win, funct_escape, &infos);
			mlx_loop(infos.mlx);
		}
	}
	return (0);
}
