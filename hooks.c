/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 15:58:47 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/11 21:48:13 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_man_and_draw(t_win *infos)
{
	infos->x_min = -2;
	infos->x_max = 1;
	infos->y_max = 1;
	infos->y_min = -1;
	infos->iter_max = 50;
	exec_and_draw(infos);
}

int		funct_key(int keycode, void *param)
{
	if (keycode == 53)
	{
		mlx_destroy_image(((t_win *)param)->mlx, ((t_win *)param)->img);
		mlx_destroy_window(((t_win *)param)->mlx, ((t_win *)param)->win);
		exit(1);
	}
	if (keycode == 3)
	{
		((t_win *)param)->fix = \
			(((t_win *)param)->fix == 0) ? 1 : 0;
		write (1, "fix parameter changed\n", 22);
	}
	if (keycode == 15)
	{
		if (((t_win *)param)->prog == 0)
			init_mandelbrot2((t_win *)param);
		else if (((t_win *)param)->prog == 1)
			init_julia2((t_win *)param);
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

int		button_press(int keycode, void *param)
{
	t_win *infos;

	infos = (t_win *)param;
	if (keycode == 69)
		(infos->iter_max) += 10;
	if (keycode == 78 && infos->iter_max >= 10)
		(infos->iter_max) -= 10;
	if (keycode == 69 || keycode == 78)
	{
		write(1, "number of iterations: ", 22);
		ft_putnbr(((t_win *)param)->iter_max);
		write(1, "\n", 1);
	}
	if (keycode == 123)
		make_column_left(infos);
	if (keycode == 124)
		make_column_right(infos);
	if (keycode == 125)
		make_line_down(infos);
	if (keycode == 126)
		make_line_up(infos);
	exec_and_draw(infos);
	return (0);
}

void	hooks(t_win *infos)
{
	mlx_key_hook(infos->win, funct_key, infos);
	mlx_mouse_hook(infos->win, funct_mouse, infos);
	mlx_hook(infos->win, 2, 2, button_press, infos);
	mlx_hook(infos->win, 6, 6, motion_mouse, infos);
	mlx_loop(infos->mlx);
}
