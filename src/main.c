/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 10:13:14 by maginist          #+#    #+#             */
/*   Updated: 2019/10/04 12:30:35 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_stocking(t_stock **start)
{
	t_stock *cur;
	t_stock *before;

	cur = *start;
	while (cur)
	{
		ft_tabdel(cur->data);
		before = cur;
		cur = cur->next;
		free(before);
		before = 0;
	}
}

int		free_map(t_map *map)
{
	free(map);
	return (0);
}

void	init_map(t_map *map)
{
	map->name = 0;
	map->color = 0;
	map->error = 0;
	map->grid = 0;
	map->max_x = 0;
	map->max_y = 0;
	map->x1 = 0;
	map->y1 = 0;
	map->mlx_ptr = 0;
	map->wind = 0;
	map->dx = 0;
	map->dy = 0;
	map->dp = 0;
	map->e = 0;
	map->ne = 0;
	map->img = 0;
	map->canvas = 0;
	map->height = 1;
	map->alpha = 0;
	map->beta = 0;
	map->phi = 0;
	map->col_0 = 0;
	map->len_t = 0;
}

int		main(int ac, char **av)
{
	t_map	*map;

	if (ac < 2)
		return (0);
	if (!(map = (t_map*)malloc(sizeof(t_map) * 1)))
		return (0);
	init_map(map);
	if (!(parsing_arg(av, map)))
		return (free_map(map));
	map->scale = (970 / map->max_x >= 540 / map->max_y ? 970
	/ map->max_x : 540 / map->max_y);
	map->move_x = 970;
	map->move_y = 540;
	map->mlx_ptr = mlx_init();
	map->wind = mlx_new_window(map->mlx_ptr, 1920, 1080, map->name);
	map->img = mlx_new_image (map->mlx_ptr, 1920, 1080.);
	map->canvas =  mlx_get_data_addr (map->img, &(map->bpp), &(map->size_line), &(map->bpp));
	free_stocking(&(map->stock));
	run_fdf(map);
	free_map(map);
	return (0);
}
