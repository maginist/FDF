/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:56:53 by maginist          #+#    #+#             */
/*   Updated: 2019/09/16 15:09:04 by maginist         ###   ########.fr       */
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
			map->color[word][i] = 0xFFFFFF;
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
	return (1);
}

int		init_grid(t_map *map, char *file)
{
	int	i;
	t_stock *cur;

	cur = map->stock;
	if (!(map->grid = (int**)malloc(sizeof(int*) * map->max_y)))
		return (0);
	if (!(map->color = (int**)malloc(sizeof(int*) * map->max_y)))
		return (0);
	i = -1;
	while (++i < map->max_y)
	{
		if (!(map->grid[i] = (int*)malloc(sizeof(int) * map->max_x)))
			return (0);
		if (!(map->color[i] = (int*)malloc(sizeof(int) * map->max_x)))
		
		if (!(recup_grid(map, cur, i)))
			return (0);
		cur = cur->next;
	}
	i = ft_strlen(file) - 4;
	file[i--] = '\0';
	while (file[i] != '/' && i > 0)
		i--;
	map->name = ft_strdup(file + i);
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
			return (0/*ft_error("Found wrong line length. Exiting.\n")*/);
		cur = map->stock;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	map->max_y++;
	return (1);
}

int		gest_fdf_file(char *file, t_map *map)
{
    int		i;
    int		fd;
    char	*line;

	map->stock = 0;
    i = ft_strlen(file);
    line = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
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
	if (!(init_grid(map, file)))
	{
		ft_printf("grid\n");
		return (0);
	}
	return (1);
}

int     parcing_arg(char **av, t_map *map)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-'/* && !(is_a_flag(av[i], &i))*/)
			return (0);
		else if (ft_strlen(av[i]) < 5
			|| ft_strcmp(&(av[i][ft_strlen(av[i]) - 4]), ".fdf")
			||  !(gest_fdf_file(av[i], map)))
		{
			ft_printf("coucou %s\n", &(av[i][ft_strlen(av[i]) - 4]));
			return (0);
		}
		i++;
	}
	return (1);
}