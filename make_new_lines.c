/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 17:47:38 by eduwer            #+#    #+#             */
/*   Updated: 2016/12/12 15:50:16 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	make_column_left(t_win *infos)
{
	infos->x_min -= infos->x_to_add * 25;
	infos->x_max -= infos->x_to_add * 25;
}

void	make_column_right(t_win *infos)
{
	infos->x_min += infos->x_to_add * 25;
	infos->x_max += infos->x_to_add * 25;
}

void	make_line_down(t_win *infos)
{
	infos->y_min -= infos->y_to_add * 25;
	infos->y_max -= infos->y_to_add * 25;
}

void	make_line_up(t_win *infos)
{
	infos->y_min += infos->y_to_add * 25;
	infos->y_max += infos->y_to_add * 25;
}
