/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:55:54 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/14 14:33:17 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	exec_and_draw(t_win *infos)
{
	if (infos->prog == 0)
		mandelbrot(infos);
	else if (infos->prog == 1)
		julia(infos);
	if (infos->prog != 2)
		mlx_put_image_to_window(infos->mlx, infos->win, infos->img, 0, 0);
}

int		get_prog_name(char *name, int nb)
{
	if (nb != 2)
		return (-1);
	if (ft_strncmp(name, "mandelbrot", 10) == 0)
		return (0);
	if (ft_strncmp(name, "julia", 5) == 0)
		return (1);
	if (ft_strcmp(name, "buddhabrot") == 0)
		return (2);
	return (-1);
}

void	print_usage_and_quit(void)
{
	write(1, "usage: ./fractol mandelbrot/julia/buddhabrot\n", 45);
	exit(1);
}

int		get_power(char *str, t_win *infos)
{
	int power;

	power = 2;
	if (infos->prog == 0)
		power = ft_atoi(&(str[10]));
	if (infos->prog == 1)
		power = ft_atoi(&(str[5]));
	if (power > 5 || power < 2)
		power = 2;
	return (power);
}

int		main(int argc, char **argv)
{
	t_win	infos;

	infos.prog = get_prog_name(argv[1], argc);
	if (infos.prog == -1)
		print_usage_and_quit();
	infos.mlx = mlx_init();
	infos.power = get_power(argv[1], &infos);
	if (infos.prog == 0)
		init_mandelbrot(&infos);
	else if (infos.prog == 1)
		init_julia(&infos);
	else if (infos.prog == 2)
		init_buddhabrot(&infos);
	hooks(&infos);
	return (0);
}
