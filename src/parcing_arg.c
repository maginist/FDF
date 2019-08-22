/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:56:53 by maginist          #+#    #+#             */
/*   Updated: 2019/08/22 18:26:08 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		parce_and_stock(char *line, t_map *map)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (line[i])
	{
		
	}
	
}

int     parcing_arg(char **av, t_map *map)
{
    int		i;
    int		fd;
    char	*line;

    i = ft_strlen(av[1]);
    line = 0;
    if (ft_strcmp(av[1][i - 5], ".fdf"))
        return (0);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
    while (get_next_line(fd, &line) > 0)
	{
		if (parce_and_stock(line, map) == 0)
			map->error = 1;
		ft_strdel(&line);
		if (map->error == 1)
			return (0);
	}
    ft_strdel(&line);
	return (1);
}