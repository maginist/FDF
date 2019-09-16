/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:13:19 by floblanc          #+#    #+#             */
/*   Updated: 2019/09/16 15:26:29 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void    run_fdf(t_map *map)
{
    void    *mlx_ptr;
    void    *wind;

    mlx_ptr = mlx_init();
    wind = mlx_new_window(mlx_ptr, map->max_x * 35, map->max_y * 40, map->name);
    ft_printf("map->y = %d && map->x %d\n", map->max_y, map->max_x);
    mlx_loop(mlx_ptr);
    mlx_pixel_put(mlx_ptr, wind, 50, 50, 65000);
    //mlx_string_put(mlx_ptr, wind, x, y, color, string)
}