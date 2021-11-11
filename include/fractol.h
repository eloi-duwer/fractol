/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:57:31 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/14 16:53:12 by eduwer           ###   ########.fr       */
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
# include <libft.h>

typedef struct	s_win
{
	pthread_mutex_t mutex_y;
	int				prog;
	void			*mlx;
	void			*win;
	void			*img;
	char			*pt_img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				pt_x;
	int				pt_y;
	double			x_to_add;
	double			y_to_add;
	double			x_min;
	double			x_max;
	double			y_min;
	double			y_max;
	int				iter_max;
	double			base_nb_real;
	double			base_nb_imag;
	int				fix;
	int				power;
	int				pixels_x;
	int				pixels_y;
}				t_win;

typedef struct	s_complex
{
	double	real_part;
	double	imag_part;
}				t_complex;

int		funct_key(int keycode, void *param);
int		funct_mouse(int button, int x, int y, void *param);
int		button_press(int keycode, void *param);
double	calc_mandelbrot(t_complex *nb, char *pt_img, t_win *infos);
void	*calc_100_lines(void *inf);
void	init_mandelbrot(t_win *infos);
void	init_mandelbrot2(t_win *infos);
void	mandelbrot(t_win *infos);
void	put_pixel_on_image(char *pt_img, int color);
void	calc_color(int i, int iter_max, char *pt_img);
void	zoom(int x, int y, t_win *infos);
void	dezoom(int x, int y, t_win *infos);
double	pow2(double nb);
void	exec_and_draw(t_win *infos);
void	make_column_left(t_win *infos);
void	make_column_right(t_win *infos);
void	make_line_down(t_win *infos);
void	make_line_up(t_win *infos);
int		motion_mouse(int x, int y, void *infos);
void	init_julia(t_win *infos);
void	init_julia2(t_win *infos);
void	julia(t_win *infos);
void	hooks(t_win *infos);
void	init_buddhabrot(t_win *infos);
void	mandel_julia_power(t_complex *nb, t_complex *result, t_win *infos);
void	init_mandel_julia_power(t_win *infos);

# endif
