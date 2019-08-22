/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 10:13:14 by maginist          #+#    #+#             */
/*   Updated: 2019/08/22 18:26:07 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	free_map(t_map *map)
{
	free(map);
	return (0);
}

int main(int ac, char **av)
{
    t_map   *map;

    if (ac < 2)
        return (0);
    if (!(map = (t_map*)malloc(sizeof(t_map) * 1)))
        return (0);
	map->color = 0;
	map->error = 0;
	map->grid = 0;
	map->max_x = 0;
	map->max_y = 0;
    if (!(parcing_arg(av, map)))
        return (free_map(map));
}