/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:57:31 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/08 17:15:06 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <complex.h>
# include "libft/libft.h"

typedef struct	s_win
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*pt_img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		pt_x;
	int		pt_y;

}				t_win;

int		funct_escape(int keycode, void *param);
int		mandelbrot(t_win *infos);
void	put_pixel_on_image(t_win *infos, int color);
void	calc_color(int i, int iter_max, t_win *infos);

# endif
