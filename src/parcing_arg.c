/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:56:53 by maginist          #+#    #+#             */
/*   Updated: 2019/09/12 17:21:45 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		recup_grid(t_map *map, t_stock *cur, int i)
{
	int		word;
	int		letter;

	word = -1;
	while (++word < cur->width)
	{
		letter = 0;
		while (cur->data[word][letter] && cur->data[word][letter] != ',')
			letter++;
		if (cur->data[word][letter])
			map->color[word][i] = ft_atoi_base(cur->data[word] + letter + 1
			, "0123456789ABCDEF", "0x");
		else
			map->color[word][i] = 0xFFFFFF00;
		cur->data[word][letter] = 0;
		letter = 0;
		if (cur->data[word][letter] == '-')
			letter++;
		while (ft_isdigit(cur->data[word][letter]))
			letter++;
		if (cur->data[word][letter] || letter > 10 || ft_atol(cur->data[word])
			> 2147483647 || ft_atol(cur->data[word]) < -2147483648)
			return (0);
		map->grid[word][i] = ft_atoi(cur->data[word]);
	}
}

int		init_grid(t_map *map)
{
	int	i;
	t_stock *cur;

	cur = map->stock;
	if (map->grid = (int**)malloc(sizeof(int*) * map->max_y))
		return (0);
	if (map->color = (int**)malloc(sizeof(int*) * map->max_y))
		return (0);
	i = -1;
	while (++i < map->max_y)
	{
		if (map->grid[i] = (int*)malloc(sizeof(int) * map->max_x))
			return (0);
		if (map->color[i] = (int*)malloc(sizeof(int) * map->max_x))
			return (0);
		if (!(recup_grid(map, cur, i)))
			return (0);
		cur = cur->next;
	}
	return (1);
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
	if (!(init_grid(map)))
		return (0);
	return (1);
}