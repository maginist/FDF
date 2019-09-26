/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:13:19 by floblanc          #+#    #+#             */
/*   Updated: 2019/09/26 16:26:06 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h>

void    seg_top_left_writer(t_map *m, int x0, int y0, int i)
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
       mlx_pixel_put(m->mlx_ptr, m->wind, x0, y0
       , m->color[i / m->max_x][i % m->max_x]);
    }
}

void    seg_left_down_writer(t_map *m, int x0, int y0, int i)
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
       mlx_pixel_put(m->mlx_ptr, m->wind, x0, y0
       , m->color[i / m->max_x][i % m->max_x]);
    }
}

void    seg_down_right_writer(t_map *m, int x0, int y0, int i)
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
       mlx_pixel_put(m->mlx_ptr, m->wind, x0, y0
       , m->color[i / m->max_x][i % m->max_x]);
    }
}

void    seg_rigth_top_writer(t_map *m, int x0, int y0, int i)
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
       mlx_pixel_put(m->mlx_ptr, m->wind, x0, y0 
       , m->color[i / m->max_x][i % m->max_x]);
    }
}

void	select_seg_sens(t_map *map, int x, int y, int i)
{
	map->x1 = (i % map->max_x) * map->scale
	- (map->grid[i / map->max_x][i % map->max_x] * (map->scale / 50 + 1)) + map->move_x;
    map->y1 = (i / map->max_x) * map->scale
	- (map->grid[i / map->max_x][i % map->max_x] * (map->scale / 50 + 1)) + map->move_y;
    if (x < map->x1 && y >= map->y1)
		seg_rigth_top_writer(map, x, y, i);
	else if (x <= map->x1 && y < map->y1)
		seg_down_right_writer(map, x, y, i);
	else if (x > map->x1 && y <= map->y1)
		seg_left_down_writer(map, x, y, i);
	else if (x >= map->x1 && y > map->y1)
		seg_top_left_writer(map, x, y, i);
}

void	write_big_pixel(t_map *map, int x, int y, int i)
{
	int x0;
	int y0;

	x0 = (i % map->max_x) * map->scale
	- (map->grid[i / map->max_x][i % map->max_x] * (map->scale / 50 + 1)) + map->move_x;
    y0 = (i / map->max_x) * map->scale
	- (map->grid[i / map->max_x][i % map->max_x] * (map->scale / 50 + 1)) + map->move_y;
    mlx_pixel_put(map->mlx_ptr, map->wind, x0, y0
	, map->color[i / map->max_x][i % map->max_x]);
}

int		key_act(int key, t_map *map)
{
	ft_printf("key = %d\n", key);
	if (key == 53)
	{
		mlx_destroy_window (map->mlx_ptr, map->wind);
		exit (0);
	}
	return (0);
}

void    run_fdf(t_map *map)
{
    int i;
    int x;
    int y;

    i = 0;
    map->mlx_ptr = mlx_init();
    map->wind = mlx_new_window(map->mlx_ptr, 1920, 1080, map->name);
    while (i / map->max_x < map->max_y)
    {
		x = (i % map->max_x) * map->scale
		- (map->grid[i / map->max_x][i % map->max_x] * (map->scale / 50 + 1)) + map->move_x;
        y = (i / map->max_x) * map->scale
		- (map->grid[i / map->max_x][i % map->max_x] * (map->scale / 50 + 1)) + map->move_y;
		write_big_pixel(map, x, y, i);
        if (i / map->max_x < map->max_y - 1)
    		select_seg_sens(map, x, y, i + map->max_x);
        if ((i + 1) % map->max_x)
			select_seg_sens(map, x, y, i + 1);
        i++;           
    }
	mlx_key_hook(map->wind, key_act, map);
	mlx_loop(map->mlx_ptr);
}