/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:13:19 by floblanc          #+#    #+#             */
/*   Updated: 2019/09/25 18:08:41 by maginist         ###   ########.fr       */
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
	while (y0 > m->y1)
    {
        if (m->dp <= 0) /* On choisit le point E */
        {
            m->dp = m->dp + m->e;
            if (m->dx >= m->dy)
                x0--;
            else
                y0--;                                
        }
        else 
        {
            m->dp = m->dp + m->ne; /* Nouveau dp */
            x0--; /* Calcul de x_p+1 */
            y0--; /* Calcul de y_p+1 */
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
	while (m->x1 < x0)
    {
        if (m->dp <= 0) /* On choisit le point E */
        {
            m->dp = m->dp + m->e;
            if (m->dx >= m->dy)
                x0--;
            else
                y0++;                                
        }
        else 
        {
            m->dp = m->dp + m->ne; /* Nouveau dp */
            x0--; /* Calcul de x_p+1 */
            y0++; /* Calcul de y_p+1 */
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
	while (m->y1 > y0)
    {
        if (m->dp <= 0) /* On choisit le point E */
        {
            m->dp = m->dp + m->e;
            if (m->dx >= m->dy)
                x0++;
			else
				y0++;
		}
        else
        {
            m->dp = m->dp + m->ne; /* Nouveau dp */
            x0++; /* Calcul de x_p+1 */
            y0++; /* Calcul de y_p+1 */
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
	while (x0 < m->x1)
    {
        if (m->dp <= 0) /* On choisit le point E */
        {
            m->dp = m->dp + m->e;
            if (m->dx >= m->dy)
                x0++;
            else
                y0--;                                
        }
        else 
        {
            m->dp = m->dp + m->ne; /* Nouveau dp */
            x0++; /* Calcul de x_p+1 */
            y0--; /* Calcul de y_p+1 */
        }
       mlx_pixel_put(m->mlx_ptr, m->wind, x0, y0 
       , m->color[i / m->max_x][i % m->max_x]);
    }
}

void	select_seg_sens(t_map *map, int x, int y, int i)
{
	map->x1 = (i % map->max_x) * map->move + (map->max_x + map->scale)
	- (map->grid[i / map->max_x][i % map->max_x]);
	map->y1 = (i / map->max_x)  * map->move + (map->max_y + map->scale) 
	- (map->grid[i / map->max_x][i % map->max_x]);
	if (i / map->max_x > 1 && i / map->max_x < 4)
		ft_printf("select : grid[%d][%d] = %d, x1 = %d, y1 = %d\n", i / map->max_x, i % map->max_x, map->grid[i / map->max_x][i % map->max_x], map->x1, map->y1);
    if (x < map->x1 && y >= map->y1)
	{
		ft_printf("right_top\n");
		seg_rigth_top_writer(map, x, y, i);
	}
	else if (x <= map->x1 && y < map->y1)
	{
		ft_printf("down_right\n");
		seg_down_right_writer(map, x, y, i);
	}
	else if (x > map->x1 && y <= map->y1)
	{
		ft_printf("left_down\n");
		seg_left_down_writer(map, x, y, i);
	}
	else if (x >= map->x1 && y > map->y1)
	{
		ft_printf("top_left\n");
		seg_top_left_writer(map, x, y, i);
	}
}

void	write_big_pixel(t_map *map, int x, int y, int i)
{
	int x0;
	int y0;

	x0 =  (i % map->max_x) * map->move + (map->max_x + map->scale)
	- (map->grid[i / map->max_x][i % map->max_x]);
	y0 = (i / map->max_x) * map->move + (map->max_y + map->scale)
	- (map->grid[i / map->max_x][i % map->max_x]);
    mlx_pixel_put(map->mlx_ptr, map->wind, x0, y0
	, map->color[i / map->max_x][i % map->max_x]);
	mlx_pixel_put(map->mlx_ptr, map->wind, x0 + 1
	, y0, map->color[i / map->max_x][i % map->max_x]);
	mlx_pixel_put(map->mlx_ptr, map->wind, x0, y0 + 1
	, map->color[i / map->max_x][i % map->max_x]);
	mlx_pixel_put(map->mlx_ptr, map->wind, x0, y0 - 1
	, map->color[i / map->max_x][i % map->max_x]);
	mlx_pixel_put(map->mlx_ptr, map->wind, x0 - 1, y0
	, map->color[i / map->max_x][i % map->max_x]);
	mlx_pixel_put(map->mlx_ptr, map->wind, x + 1, y 
	, map->color[i / map->max_x][i % map->max_x]);
	mlx_pixel_put(map->mlx_ptr, map->wind, x, y + 1
	, map->color[i / map->max_x][i % map->max_x]);
	mlx_pixel_put(map->mlx_ptr, map->wind, x - 1, y 
	, map->color[i / map->max_x][i % map->max_x]);
	mlx_pixel_put(map->mlx_ptr, map->wind, x, y - 1
	, map->color[i / map->max_x][i % map->max_x]);
}

void    run_fdf(t_map *map)
{
    int i;
    int x;
    int y;

    i = 0;
    map->mlx_ptr = mlx_init();
    map->wind = mlx_new_window(map->mlx_ptr, map->max_x * 40, map->max_y * 40, map->name);
    ft_printf("map->y = %d && map->x %d\n", map->max_y, map->max_x);
    while (i / map->max_x < map->max_y)
    {
		x = (i % map->max_x) * map->move + (map->max_x + map->scale)
		- (map->grid[i / map->max_x][i % map->max_x]);
        y = (i / map->max_x) * map->move + (map->max_y + map->scale)
		- (map->grid[i / map->max_x][i % map->max_x]);
		if (i / map->max_x > 1 && i / map->max_x < 4)
			ft_printf("\tgrid[%d][%d] = %d, x = %d, y = %d\n", i / map->max_x, i % map->max_x, map->grid[i / map->max_x][i % map->max_x], x, y);
		write_big_pixel(map, x, y, i);
        if (i / map->max_x < map->max_y - 1)
		{
			ft_printf("i / max_x\n");
    		select_seg_sens(map, x, y, i + map->max_x);
		}
        if ((i + 1) % map->max_x)
    	{
			ft_printf("i + 1\n");
			select_seg_sens(map, x, y, i + 1);
		}
        i++;           
    }
    mlx_loop(map->mlx_ptr);
}