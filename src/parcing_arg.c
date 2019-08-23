/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:56:53 by maginist          #+#    #+#             */
/*   Updated: 2019/08/23 11:24:47 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		recup_grid(t_map *map)
{
	int	i;
	t_stock *cur;

	cur = map->stock;
	if (map->grid = (int**)malloc(sizeof(int*) * map->max_y))
		return (0);
	if (map->color = (int**)malloc(sizeof(int*) * map->max_y))
		return (0);
	i = 0;
	while (cur)
	{

	}
}

int		parce_and_stock(char *line, t_map *map)
{
	t_stock	*new;
	t_stock	*cur;

	if (!(new = (t_stock*)malloc(sizeof(t_stock) * 1)))
		return (0);
	new->data = ft_strsplit(line, ' ');
	new->next = 0;
	if (!(map->stock))
	{
		map->stock = new;
		map->max_x = ft_tab2size((void**)(new->data));
	}
	else
	{
		if (ft_tab2size((void**)(new->data)) != map->max_x)
			return (ft_error("Found wrong line length. Exiting.\n"));
		cur = map->stock;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	map->max_y++;	
}

int     parcing_arg(char **av, t_map *map)
{
    int		i;
    int		fd;
    char	*line;

	map->stock = 0;
    i = ft_strlen(av[1]);
    line = 0;
    if (ft_strcmp(av[1][i - 5], ".fdf"))
        return (0);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	i = 0;
    while (get_next_line(fd, &line) > 0)
	{
		if (parce_and_stock(line, map) == 0)
			map->error = 1;
		ft_strdel(&line);
		if (map->error == 1)
			return (0);
	}
    ft_strdel(&line);
	if (!(recup_grid(map)))
		return (0);
	return (1);
}