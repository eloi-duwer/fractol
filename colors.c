/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 17:12:41 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/08 17:57:59 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calc_color(int i, int iter_max, t_win *infos)
{
	int		color;
	double	proportion;

	if (i == iter_max)
		put_pixel_on_image(infos, 0x0);
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
		put_pixel_on_image(infos, color);
	}
}
