/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:13:19 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/02 17:38:05 by floblanc         ###   ########.fr       */
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
	int	z;

	z = map->grid[i / map->max_x][i % map->max_x]  * map->height;
	x0 = (int)(((i % map->max_x - map->max_x / 2) * cos(map->beta)
		+ z * sin(map->beta)
		+ (i % map->max_x - map->max_x / 2) * cos(map->phi)
		- (i / map->max_x - map->max_y / 2) * sin(map->phi)) * map->scale)
		+ map->move_x;
	y0 = (int)(((i / map->max_x - map->max_y / 2) * cos(map->alpha)
		- z * sin(map->alpha)
		+ (i % map->max_x - map->max_x / 2) * sin(map->phi)
		+ (i / map->max_x - map->max_y / 2) * cos(map->phi)) * map->scale)
		+ map->move_y;
	if (y >= 0 && y <= 1080 && x >= 0 && x <= 1920)
		*(int *)&map->canvas[y * map->size_line + (x * 4)] = map->color[i / map->max_x][i % map->max_x];
}

int		key_act(int key, t_map *map)
{
	ft_printf("key = %d && scale = %f\n", key, map->scale);
	if (key == 53)
	{
		mlx_destroy_window(map->mlx_ptr, map->wind);
		exit(0);
		return (0);
	}
	if (key == 69)
		map->scale++;
	if (key == 78 && map->scale - 1 > 0)
		map->scale--;
	if (key == 123 && map->move_x - 1 > 0)
		map->move_x -= 5;
	if (key == 126 && map->move_y - 1 > 0)
		map->move_y -= 5;
	if (key == 124)
		map->move_x += 5;
	if (key == 125)
		map->move_y += 5;
	if (key == 83)
		map->height -= 0.1;
	if (key == 85)
		map->height += 0.1;
	if (key == 86)
		map->beta -= M_PI / 16;
	if (key == 89)
		map->beta += M_PI / 16;
	if (key == 91)
		map->phi -= M_PI / 16;
	if (key == 87)
		map->phi += M_PI / 16;
	if (key == 92)
		map->alpha -= M_PI / 16;
	if (key == 88)
		map->alpha += M_PI / 16;
	run_fdf(map);
	return (1);
}

void	run_fdf(t_map *map)
{
	int i;
	int x;
	int y;
	int	z;

	i = 0;
	ft_bzero(map->canvas, 4 * 1920 * 1080);
	while (i / map->max_x < map->max_y)
	{
		z = map->grid[i / map->max_x][i % map->max_x] * map->height;
		x = (int)(((i % map->max_x - map->max_x / 2) * cos(map->beta)
		+ z * sin(map->beta)
		+ (i % map->max_x - map->max_x / 2) * cos(map->phi)
		- (i / map->max_x - map->max_y / 2) * sin(map->phi)) * map->scale)
		+ map->move_x;
		y = (int)(((i / map->max_x - map->max_y / 2) * cos(map->alpha)
		- z * sin(map->alpha)
		+ (i % map->max_x - map->max_x / 2) * sin(map->phi)
		+ (i / map->max_x - map->max_y / 2) * cos(map->phi)) * map->scale)
		+ map->move_y;
		write_pixel(map, x, y, i);
		if (i / map->max_x < map->max_y - 1)
			select_seg_sens(map, x, y, i + map->max_x);
		if ((i + 1) % map->max_x)
			select_seg_sens(map, x, y, i + 1);
		i++;
	}
	ft_printf("cos(%f)/sin = %f && %f\n", map->phi, cos(map->phi), sin(map->phi));
	mlx_put_image_to_window (map->mlx_ptr, map->wind, map->img, 0, 0);
	mlx_hook(map->wind, 17, 0, red_cross, map);
	mlx_hook(map->wind, 2, 0, key_act, map);
	mlx_loop(map->mlx_ptr);
}
