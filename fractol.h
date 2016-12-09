/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:57:31 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/09 15:37:54 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <complex.h>
# include "libft/libft.h"

typedef struct	s_win
{
	pthread_mutex_t mutex_y;
	void	*mlx;
	void	*win;
	void	*img;
	char	*pt_img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		pt_x;
	int		pt_y;
	double	x_to_add;
	double	y_to_add;
}				t_win;

int		funct_escape(int keycode, void *param);
int		mandelbrot(t_win *infos);
void	put_pixel_on_image(char *pt_img, int color);
void	calc_color(int i, int iter_max, char *pt_img);

# endif
