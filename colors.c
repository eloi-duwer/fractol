/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 17:12:41 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/10 12:22:53 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel_on_image(char *pt_img, int color)
{
	int				i;
	unsigned char	*color_pt;
	char			*pt_img_pixel;

	color_pt = (unsigned char *)&color;
	pt_img_pixel = pt_img;
	i = 0;
	while (i < 3)
	{
		*pt_img_pixel = *color_pt;
		pt_img_pixel++;
		color_pt++;
		i++;
	}
}

void	calc_color(int i, int iter_max, char *pt_img)
{
	int		color;
	double	proportion;

	if (i == iter_max)
		put_pixel_on_image(pt_img, 0x0);
	else
	{
		proportion = (double)i / (double)iter_max;
		if (proportion < 0.25)
		{
			color = 0xFF0000;
			color += 0x000100 * (int)(nearbyint(proportion * 1024.0));
		}
		else
		{
			proportion -= 0.25;
			color = 0xFFFF00;
			color -= 0x010100 * (int)(nearbyint(proportion * 341.33));
			color += 0x000001 * (int)(nearbyint(proportion * 341.33));
		}
		put_pixel_on_image(pt_img, color);
	}
}
