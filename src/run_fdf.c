/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:13:19 by floblanc          #+#    #+#             */
/*   Updated: 2019/09/17 16:06:08 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void    run_fdf(t_map *map)
{
    void    *mlx_ptr;
    void    *wind;
    int i  = 0;

    mlx_ptr = mlx_init();
    wind = mlx_new_window(mlx_ptr, map->max_x * 40, map->max_y * 40, map->name);
    ft_printf("map->y = %d && map->x %d\n", map->max_y, map->max_x);
    while (i / map->max_x < map->max_y)
    {
        if (i % map->max_x == 0 && i != 0)
            ft_printf("\n");
        mlx_pixel_put(mlx_ptr, wind, i % map->max_x * 10 + 5, i / map->max_x * 10 + 5, 0xFFFFFF - (map->grid[i / map->max_x][i % map->max_x] * 1000000));
        mlx_pixel_put(mlx_ptr, wind, i % map->max_x * 10 + 6, i / map->max_x * 10 + 5, 0xFFFFFF - (map->grid[i / map->max_x][i % map->max_x] * 1000000));
        mlx_pixel_put(mlx_ptr, wind, i % map->max_x * 10 + 6, i / map->max_x * 10 + 6, 0xFFFFFF - (map->grid[i / map->max_x][i % map->max_x] * 1000000));
        mlx_pixel_put(mlx_ptr, wind, i % map->max_x * 10 + 5, i / map->max_x * 10 + 6, 0xFFFFFF - (map->grid[i / map->max_x][i % map->max_x] * 1000000));
        mlx_pixel_put(mlx_ptr, wind, i % map->max_x * 10 + 7, i / map->max_x * 10 + 5, 0xFFFFFF - (map->grid[i / map->max_x][i % map->max_x] * 1000000));
        mlx_pixel_put(mlx_ptr, wind, i % map->max_x * 10 + 7, i / map->max_x * 10 + 6, 0xFFFFFF - (map->grid[i / map->max_x][i % map->max_x] * 1000000));
        mlx_pixel_put(mlx_ptr, wind, i % map->max_x * 10 + 7, i / map->max_x * 10 + 7, 0xFFFFFF - (map->grid[i / map->max_x][i % map->max_x] * 1000000));
        mlx_pixel_put(mlx_ptr, wind, i % map->max_x * 10 + 5, i / map->max_x * 10 + 7, 0xFFFFFF - (map->grid[i / map->max_x][i % map->max_x] * 1000000));
        mlx_pixel_put(mlx_ptr, wind, i % map->max_x * 10 + 6, i / map->max_x * 10 + 7, 0xFFFFFF - (map->grid[i / map->max_x][i % map->max_x] * 1000000));
        ft_printf("%d\t", map->grid[i / map->max_x][i % map->max_x]);
        i++;
    }
    mlx_loop(mlx_ptr);
    //mlx_string_put(mlx_ptr, wind, x, y, color, string)
}