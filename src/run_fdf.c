/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:13:19 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/01 16:37:09 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int red_cross(t_map *map)
{
	free_map(map);
	exit(0);
	return (0);
}

void	write_pixel(t_map *map, int x, int y, int i)
{
	int x0;
	int y0;

	x0 = (i % map->max_x) * map->scale
		- (map->grid[i / map->max_x][i % map->max_x] * (map->scale / 50 + 1))
		+ map->move_x;
	y0 = (i / map->max_x) * map->scale
		- (map->grid[i / map->max_x][i % map->max_x] * (map->scale / 50 + 1))
		+ map->move_y;
	if (y >= 0 && y <= 1080 && x >= 0 && x <= 1920)
		*(int *)&map->canvas[y * map->size_line + (x * 4)] = map->color[i / map->max_x][i % map->max_x];
}

int		key_act(int key, t_map *map)
{
	ft_printf("key = %d && scale = %d\n", key, map->scale);
	if (key == 53)
	{
		mlx_destroy_window(map->mlx_ptr, map->wind);
		exit(0);
		return (0);
	}
	if (key == 69)
		map->scale += 5;
	if (key == 78 && map->scale - 5 > 0)
		map->scale -= 5;
	if (key == 123 && map->move_x - 5 > 0)
		map->move_x -= 5;
	if (key == 126 && map->move_y - 5 > 0)
		map->move_y -= 5;
	if (key == 124)
		map->move_x += 5;
	if (key == 125)
		map->move_y += 5;
	run_fdf(map);
	return (1);
}

void	run_fdf(t_map *map)
{
	int i;
	int x;
	int y;

	i = 0;
	ft_bzero(map->canvas, 4 * 1920 * 1080);
	while (i / map->max_x < map->max_y)
	{
		x = (i % map->max_x) * map->scale
			- (map->grid[i / map->max_x][i % map->max_x]
			* (map->scale / 50 + 1)) + map->move_x;
		y = (i / map->max_x) * map->scale
			- (map->grid[i / map->max_x][i % map->max_x]
			* (map->scale / 50 + 1)) + map->move_y;
		write_pixel(map, x, y, i);
		if (i / map->max_x < map->max_y - 1)
			select_seg_sens(map, x, y, i + map->max_x);
		if ((i + 1) % map->max_x)
			select_seg_sens(map, x, y, i + 1);
		i++;
	}
	mlx_put_image_to_window (map->mlx_ptr, map->wind, map->img, 0, 0);
	mlx_hook(map->wind, 17, 0, red_cross, map);
	mlx_hook(map->wind, 2, 0, key_act, map);
	mlx_loop(map->mlx_ptr);
}
