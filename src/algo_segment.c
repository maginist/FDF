/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 19:00:19 by maginist          #+#    #+#             */
/*   Updated: 2019/10/01 16:36:42 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	seg_top_left_writer(t_map *m, int x0, int y0, int i)
{
	m->dx = x0 - m->x1;
	m->dy = y0 - m->y1;
	m->dp = (m->dx >= m->dy ? 2 * m->dy - m->dx : 2 * m->dx - m->dy);
	m->e = (m->dx >= m->dy ? 2 * m->dy : 2 * m->dx);
	m->ne = (m->dx >= m->dy ? 2 * (m->dy - m->dx) : 2 * (m->dx - m->dy));
	while (y0 > m->y1 || x0 > m->x1)
	{
		if (m->dp <= 0)
		{
			m->dp = m->dp + m->e;
			if (m->dx >= m->dy)
				x0--;
			else
				y0--;
		}
		else
		{
			m->dp = m->dp + m->ne;
			x0--;
			y0--;
		}
		if (y0 >= 0 && y0 <= 1080 && x0 >= 0 && x0 <= 1920)
			*(int *)&m->canvas[y0 * m->size_line + (x0 * 4)] = m->color[i / m->max_x][i % m->max_x];
	}
}

void	seg_left_down_writer(t_map *m, int x0, int y0, int i)
{
	m->dx = x0 - m->x1;
	m->dy = m->y1 - y0;
	m->dp = (m->dx >= m->dy ? 2 * m->dy - m->dx : 2 * m->dx - m->dy);
	m->e = (m->dx >= m->dy ? 2 * m->dy : 2 * m->dx);
	m->ne = (m->dx >= m->dy ? 2 * (m->dy - m->dx) : 2 * (m->dx - m->dy));
	while (m->x1 < x0 || y0 < m->y1)
	{
		if (m->dp <= 0)
		{
			m->dp = m->dp + m->e;
			if (m->dx >= m->dy)
				x0--;
			else
				y0++;
		}
		else
		{
			m->dp = m->dp + m->ne;
			x0--;
			y0++;
		}
		if (y0 >= 0 && y0 <= 1080 && x0 >= 0 && x0 <= 1920)
			*(int *)&m->canvas[y0 * m->size_line + (x0 * 4)] = m->color[i / m->max_x][i % m->max_x];
	}
}

void	seg_down_right_writer(t_map *m, int x0, int y0, int i)
{
	m->dx = m->x1 - x0;
	m->dy = m->y1 - y0;
	m->dp = (m->dx >= m->dy ? 2 * m->dy - m->dx : 2 * m->dx - m->dy);
	m->e = (m->dx >= m->dy ? 2 * m->dy : 2 * m->dx);
	m->ne = (m->dx >= m->dy ? 2 * (m->dy - m->dx) : 2 * (m->dx - m->dy));
	while (m->y1 > y0 || x0 < m->x1)
	{
		if (m->dp <= 0)
		{
			m->dp = m->dp + m->e;
			if (m->dx >= m->dy)
				x0++;
			else
				y0++;
		}
		else
		{
			m->dp = m->dp + m->ne;
			x0++;
			y0++;
		}
		if (y0 >= 0 && y0 <= 1080 && x0 >= 0 && x0 <= 1920)
			*(int *)&m->canvas[y0 * m->size_line + (x0 * 4)] = m->color[i / m->max_x][i % m->max_x];
	}
}

void	seg_rigth_top_writer(t_map *m, int x0, int y0, int i)
{
	m->dx = m->x1 - x0;
	m->dy = y0 - m->y1;
	m->dp = (m->dx >= m->dy ? 2 * m->dy - m->dx : 2 * m->dx - m->dy);
	m->e = (m->dx >= m->dy ? 2 * m->dy : 2 * m->dx);
	m->ne = (m->dx >= m->dy ? 2 * (m->dy - m->dx) : 2 * (m->dx - m->dy));
	while (x0 < m->x1 || y0 > m->y1)
	{
		if (m->dp <= 0)
		{
			m->dp = m->dp + m->e;
			if (m->dx >= m->dy)
				x0++;
			else
				y0--;
		}
		else
		{
			m->dp = m->dp + m->ne;
			x0++;
			y0--;
		}
		if (y0 >= 0 && y0 <= 1080 && x0 >= 0 && x0 <= 1920)
			*(int *)&m->canvas[y0 * m->size_line + (x0 * 4)] = m->color[i / m->max_x][i % m->max_x];
	}
}

void	select_seg_sens(t_map *map, int x, int y, int i)
{
	map->x1 = (i % map->max_x) * map->scale
	- (map->grid[i / map->max_x][i % map->max_x] * (map->scale / 50 + 1))
	+ map->move_x;
	map->y1 = (i / map->max_x) * map->scale
	- (map->grid[i / map->max_x][i % map->max_x]
	* (map->scale / 50 + 1)) + map->move_y;
	if (x < map->x1 && y >= map->y1)
		seg_rigth_top_writer(map, x, y, i);
	else if (x <= map->x1 && y < map->y1)
		seg_down_right_writer(map, x, y, i);
	else if (x > map->x1 && y <= map->y1)
		seg_left_down_writer(map, x, y, i);
	else if (x >= map->x1 && y > map->y1)
		seg_top_left_writer(map, x, y, i);
}
