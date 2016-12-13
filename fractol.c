/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:55:54 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/13 16:42:48 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	exec_and_draw(t_win *infos)
{
	if (infos->prog == 0)
		mandelbrot(infos);
	else if (infos->prog == 1)
		julia(infos);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->img, 0, 0);
}

int		get_prog_name(char *name, int nb)
{
	if (nb != 2)
		return (-1);
	if (ft_strcmp(name, "mandelbrot") == 0)
		return (0);
	if (ft_strcmp(name, "julia") == 0)
		return (1);
	if (ft_strcmp(name, "buddhabrot") == 0)
		return (2);
	return (-1);
}

void	print_usage_and_quit(void)
{
	write(1, "usage: ./fractol mandelbrot/julia/other\n", 40);
	exit(1);
}

int		main(int argc, char **argv)
{
	t_win	infos;

	infos.prog = get_prog_name(argv[1], argc);
	if (infos.prog == -1)
		print_usage_and_quit();
	infos.mlx = mlx_init();
	if (infos.prog == 0)
		init_mandelbrot(&infos);
	else if (infos.prog == 1)
		init_julia(&infos);
	else if (infos.prog == 2)
		init_buddhabrot(&infos);
	if (infos.prog == 2)
		infos.win = mlx_new_window(infos.mlx, 1000, 1350, argv[1]);
	else
		infos.win = mlx_new_window(infos.mlx, 1500, 1000, argv[1]);
	mlx_put_image_to_window(infos.mlx, infos.win, infos.img, 0, 0);
	hooks(&infos);
	return (0);
}
