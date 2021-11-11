/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 15:58:47 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/13 18:40:47 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <fractol.h>

int		funct_key(int keycode, void *param)
{
	t_win *infos;

	infos = (t_win *)param;
	if (keycode == XK_Escape)
	{
		mlx_destroy_image(infos->mlx, infos->img);
		mlx_destroy_window(infos->mlx, infos->win);
		exit(1);
	}
	if (keycode == XK_f)
	{
		infos->fix = (infos->fix == 0) ? 1 : 0;
		write(1, "fix parameter changed\n", 22);
	}
	if (keycode == XK_plus || keycode == XK_equal) // No check for modifiers...
		(infos->iter_max) += 10;
	if (keycode == XK_minus && infos->iter_max >= 10)
		(infos->iter_max) -= 10;
	if (keycode == XK_plus || keycode == XK_minus || keycode == XK_equal)
	{
		write(1, "number of iterations: ", 22);
		ft_putnbr(((t_win *)param)->iter_max);
		write(1, "\n", 1);
	}
	if (keycode == XK_Left)
		make_column_left(infos);
	if (keycode == XK_Right)
		make_column_right(infos);
	if (keycode == XK_Down)
		make_line_down(infos);
	if (keycode == XK_Up)
		make_line_up(infos);
	exec_and_draw(infos);
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

void	hooks(t_win *infos)
{
	mlx_key_hook(infos->win, funct_key, infos);
	mlx_mouse_hook(infos->win, funct_mouse, infos);
	mlx_hook(infos->win, MotionNotify, PointerMotionMask, motion_mouse, infos);
	mlx_loop(infos->mlx);
}
