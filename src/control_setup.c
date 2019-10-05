/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:05:06 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/05 12:19:09 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	write_hud2(t_map *map)
{
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 610, 0xFFFFFF, "  C");
	mlx_string_put(map->mlx_ptr, map->wind, 1740, 660, 0xFFFFFF, "POV");
	mlx_string_put(map->mlx_ptr, map->wind, 1740, 690, 0xFFFFFF, " 2 ");
	mlx_string_put(map->mlx_ptr, map->wind, 1740, 740, 0xFFFFFF, "CLOSE ");
	mlx_string_put(map->mlx_ptr, map->wind, 1740, 770, 0xFFFFFF, " esc ");
	mlx_string_put(map->mlx_ptr, map->wind, 1740, 820, 0xFFFFFF, "RESET ");
	mlx_string_put(map->mlx_ptr, map->wind, 1740, 850, 0xFFFFFF, " R ");
}

void	write_hud(t_map *map)
{
	int	x;
	int	y;

	x = 1600;
	y = 200;
	while (x++ < 1920)
		mlx_pixel_put(map->mlx_ptr, map->wind, x, y, 0x00FFFF);
	x = 1600;
	while (y++ < 900)
		mlx_pixel_put(map->mlx_ptr, map->wind, x, y, 0x00FFFF);
	while (x++ < 1920)
		mlx_pixel_put(map->mlx_ptr, map->wind, x, y, 0x00FFFF);
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 200, 0xFFFFFF, "~ HUD ~");
	mlx_string_put(map->mlx_ptr, map->wind, 1740, 250, 0xFFFFFF, "ZOOM");
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 270, 0xFFFFFF, " + / -");
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 320, 0xFFFFFF, "MOVEMENT");
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 340, 0xFFFFFF, " arrows");
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 390, 0xFFFFFF, "ROTATION");
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 410, 0xFFFFFF, " x = 7 / 4");
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 430, 0xFFFFFF, " y = 8 / 5");
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 450, 0xFFFFFF, " z = 9 / 6");
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 500, 0xFFFFFF, "- HEIGHT +");
	mlx_string_put(map->mlx_ptr, map->wind, 1750, 530, 0xFFFFFF, "1 / 3");
	mlx_string_put(map->mlx_ptr, map->wind, 1730, 580, 0xFFFFFF, "COLOR");
	write_hud2(map);
}

void	reset_act(t_map *map)
{
	map->alpha = 0;
	map->beta = 0;
	map->phi = 0;
	map->height = 1;
	map->scale = (970 / map->max_x >= 540 / map->max_y ? 970
		/ map->max_x : 540 / map->max_y);
	map->move_x = 970;
	map->move_y = 540;
}

int		key_act2(int key, t_map *map)
{
	if (key == 89)
		map->alpha += M_PI / 24;
	if (key == 87)
		map->beta -= M_PI / 24;
	if (key == 91)
		map->beta += M_PI / 24;
	if (key == 88)
		map->phi -= M_PI / 24;
	if (key == 92)
		map->phi += M_PI / 24;
	if (key == 15)
		reset_act(map);
	if (key == 84)
	{
		map->alpha = M_PI / 5;
		map->beta = M_PI / 10;
		map->phi = 15 * M_PI / 8;
	}
	map->alpha = (cos(map->alpha) != 1 ? map->alpha : 0);
	map->beta = (cos(map->beta) != 1 ? map->beta : 0);
	map->phi = (cos(map->phi) != 1 ? map->phi : 0);
	run_fdf(map);
	return (1);
}

int		key_act(int key, t_map *map)
{
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
		map->height -= 0.05;
	if (key == 85)
		map->height += 0.05;
	if (key == 86)
		map->alpha -= M_PI / 24;
	return (key_act2(key, map));
}
