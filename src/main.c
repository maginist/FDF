/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 10:13:14 by maginist          #+#    #+#             */
/*   Updated: 2019/09/25 17:48:15 by maginist         ###   ########.fr       */
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

int	free_map(t_map *map)
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
	map->move = 30;
	map->scale = 30;
	map->dx = 0;
	map->dy = 0;
	map->dp = 0;
	map->e = 0;
	map->ne = 0;
}

int main(int ac, char **av)
{
    t_map   *map;

    if (ac < 2)
        return (0);
    if (!(map = (t_map*)malloc(sizeof(t_map) * 1)))
        return (0);
	init_map(map);
	ft_printf("OK GOOGLE\n");
    if (!(parcing_arg(av, map)))
        return (free_map(map));
	ft_printf("OK GOOGLE2\n");
	free_stocking(&(map->stock));
	run_fdf(map);
	return (0);
}