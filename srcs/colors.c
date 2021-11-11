/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 17:12:41 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/13 16:18:13 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	put_pixel_on_image(char *pt_img, int color)
{
	int				i;
	unsigned char	*color_pt;

	color_pt = (unsigned char *)&color;
	i = 0;
	while (i < 3)
	{
		*pt_img = *color_pt;
		pt_img++;
		color_pt++;
		i++;
	}
}

int		white_to_yellow(double proportion)
{
	int color;

	if (proportion <= 0.03125)
	{
		color = 0xFFFFFF;
		color -= 0x000101 * (int)(nearbyint(proportion * 8160));
	}
	else
	{
		proportion -= 0.03125;
		color = 0xFF0000;
		color += 0x000100 * (int)(nearbyint(proportion * 8160));
	}
	return (color);
}

int		yellow_to_blue_sky(double proportion)
{
	int color;

	if (proportion <= 0.125)
	{
		proportion -= 0.0625;
		color = 0xFFFF00;
		color -= 0x010000 * (int)(nearbyint(proportion * 4080));
	}
	else
	{
		proportion -= 0.125;
		color = 0x00FF00;
		color += 0x000001 * (int)(nearbyint(proportion * 2040));
	}
	return (color);
}

int		blue_sky_to_purple(double proportion)
{
	int color;

	if (proportion <= 0.5)
	{
		proportion -= 0.25;
		color = 0x00FFFF;
		color -= 0x000100 * (int)(nearbyint(proportion * 1020));
	}
	else
	{
		proportion -= 0.5;
		color = 0x0000FF;
		color += 0x010000 * (int)(nearbyint(proportion * 510));
	}
	return (color);
}

void	calc_color(int i, int iter_max, char *pt_img)
{
	int		color;
	double	proportion;

	color = 0x0;
	if (i == iter_max)
		put_pixel_on_image(pt_img, color);
	else
	{
		proportion = (double)i / (double)iter_max;
		if (proportion <= 0.0625)
			color = white_to_yellow(proportion);
		else if (proportion <= 0.25)
			color = yellow_to_blue_sky(proportion);
		else if (proportion <= 1)
			color = blue_sky_to_purple(proportion);
		put_pixel_on_image(pt_img, color);
	}
}
