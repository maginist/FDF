/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:56:53 by maginist          #+#    #+#             */
/*   Updated: 2019/09/26 19:30:24 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		parse_split(t_stock *cur, int letter, int word)
{
	cur->data[word][letter] = 0;
	letter = 0;
	if (cur->data[word][letter] == '-')
		letter++;
	while (ft_isdigit(cur->data[word][letter]))
		letter++;
	if (cur->data[word][letter] || letter > 10 || ft_atol(cur->data[word])
			> 2147483647 || ft_atol(cur->data[word]) < -2147483648)
		return (0);
	return (1);
}

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
		{
			if (!(map->color[i][word] = ft_atoi_base(cur->data[word] + letter
							+ 1, "0123456789ABCDEF", "0x")))
				map->color[i][word] = ft_atoi_base(cur->data[word] + letter + 1
						, "0123456789abcdef", "0x");
		}
		else
			map->color[i][word] = 0xFFFFFF;
		if (!(parse_split(cur, letter, word)))
			return (0);
		map->grid[i][word] = ft_atoi(cur->data[word]);
	}
	return (1);
}

int		init_grid(t_map *map, char *file)
{
	int		i;
	t_stock	*cur;

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
			return (0);
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

int		parse_and_stock(char *line, t_map *map)
{
	t_stock	*new;
	t_stock	*cur;

	if (!(new = (t_stock*)malloc(sizeof(t_stock) * 1)))
		return (0);
	new->data = ft_strsplit(line, ' ');
	new->next = 0;
	new->width = ft_tab2size((void**)(new->data));
	if (!(map->stock))
	{
		map->stock = new;
		map->max_x = new->width;
	}
	else
	{
		if (new->width != map->max_x)
			return (0);
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
		if (parse_and_stock(line, map) == 0)
			map->error = 1;
		ft_strdel(&line);
		if (map->error == 1)
			return (0);
	}
	ft_strdel(&line);
	if (!(init_grid(map, file)))
		return (0);
	return (1);
}

int		parsing_arg(char **av, t_map *map)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-')
			return (0);
		else if (ft_strlen(av[i]) < 5
				|| ft_strcmp(&(av[i][ft_strlen(av[i]) - 4]), ".fdf")
				|| !(gest_fdf_file(av[i], map)))
			return (0);
		i++;
	}
	return (1);
}
