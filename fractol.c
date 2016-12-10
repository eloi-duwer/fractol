/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:55:54 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/10 19:24:18 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		funct_key(int keycode, void *param)
{
	if (keycode == 53)
	{
		mlx_destroy_image(((t_win *)param)->mlx, ((t_win *)param)->img);
		mlx_destroy_window(((t_win *)param)->mlx, ((t_win *)param)->win);
		exit(1);
	}
	return (0);
}

int		funct_mouse(int button, int x, int y, void *param)
{
	if (button == 5)
		zoom(x, y, (t_win *)param);
	if (button == 4)
		dezoom(x, y, (t_win *)param);
	return (0);
}

int		main(int argc, char **argv)
{
	t_win	infos;
	int		ret;

	infos.mlx = mlx_init();
	pthread_mutex_init(&(infos.mutex_y), NULL);
	ret = 0;
	if (argc >= 2)
	{
		if (ft_strcmp(argv[1], "mandelbrot") == 0)
			ret = init_mandelbrot(&infos);
		if (ret == 1)
		{
			infos.win = mlx_new_window(infos.mlx, 1500, 1000, argv[1]);
			mlx_put_image_to_window(infos.mlx, infos.win, infos.img, 0, 0);
			mlx_key_hook(infos.win, funct_key, &infos);
			mlx_mouse_hook(infos.win, funct_mouse, &infos);
			mlx_loop(infos.mlx);
		}
	}
	return (0);
}
