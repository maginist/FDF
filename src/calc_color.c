/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 11:45:27 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/04 13:51:59 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		calc_color(t_map *m, int x0, int y0, int i)
{
	double	div;
	int		red_d;
	int		green_d;
	int		blue_d;
	int		res;

	div =((double)m->len_t - sqrt(pow(m->x1 - x0,2) + pow(m->y1 - y0, 2)))
	/ (double)m->len_t;
	red_d = (m->color[i / m->max_x][i % m->max_x] & 0xFF0000)
	- (m->col_0 & 0xFF0000);
	red_d = (int)(red_d * div);
	green_d = (m->color[i / m->max_x][i % m->max_x] & 0xFF00)
	- (m->col_0 & 0xFF00);
	green_d = (int)(green_d * div);
	blue_d = (m->color[i / m->max_x][i % m->max_x] & 0xFF)
	- (m->col_0 & 0xFF);
	blue_d = (int)(blue_d * div);
	res = m->col_0;
	res += (red_d - red_d % 0x10000) + (green_d - green_d % 0x100) + blue_d;
	return (res);
}