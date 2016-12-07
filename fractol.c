/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:55:54 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/07 18:57:41 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		funct_escape(int keycode, void *param)
{
	if (keycode == 53)
	{
		mlx_destroy_window(((t_win *)param)->mlx, ((t_win *)param)->win);
		exit (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_win infos;
	int ret;

	infos.mlx = mlx_init();
	ret = 0;
	if (argc >= 2)
	{
		if (ft_strcmp(argv[1], "mandelbrot") == 0)
			ret = mandelbrot(&infos);
		if (ret == 1)
		{
			mlx_key_hook(infos.win, funct_escape, &infos);
			mlx_loop(infos.win);
		}
	}
	return (0);
}
