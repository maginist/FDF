/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:13:19 by floblanc          #+#    #+#             */
/*   Updated: 2019/09/18 18:32:53 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	trace_segment(t_map *map, int i, int x, int y)
{
	
}

void    run_fdf(t_map *map)
{
    int i;
    
    i = 0;
    map->mlx_ptr = mlx_init();
    map->wind = mlx_new_window(map->mlx_ptr, map->max_x * 100, map->max_y * 100, map->name);
    ft_printf("map->y = %d && map->x %d\n", map->max_y, map->max_x);
    while (i / map->max_x < map->max_y)
    {
        if (i % map->max_x == 0 && i != 0)
            ft_printf("\n");
        mlx_pixel_put(map->mlx_ptr, map->wind
        , i % map->max_x * 50 + (map->max_x * 25) - (map->grid[i / map->max_x][i % map->max_x])
        , i / map->max_x * 50 + (map->max_y * 25) - (map->grid[i / map->max_x][i % map->max_x])
        , 0xFFFFFF - (map->grid[i / map->max_x][i % map->max_x] * 100000));
        //ft_printf("%d\t", map->grid[i / map->max_x][i % map->max_x]);
        trace_segment(map, i, i % map->max_x * 50 + (map->max_x * 25) - (map->grid[i / map->max_x][i % map->max_x]), i / map->max_x * 50 + (map->max_x * 25) - (map->grid[i / map->max_x][i % map->max_x]));
        i++;
    }
    mlx_loop(map->mlx_ptr);
}