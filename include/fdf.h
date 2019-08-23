/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 10:11:20 by maginist          #+#    #+#             */
/*   Updated: 2019/08/23 11:21:55 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libprintf/include/libprintf.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>

typedef struct		s_stock
{
	char			**data;
	int				width;
	struct s_stock	*next;
}					t_stock;

typedef struct		s_map
{
    int				**grid;
	int 			**color;
    int				max_x;
	int				max_y;
	int				error;
	t_stock			*stock;
}					t_map;

int				main(int ac, char **av);
int				parcing_arg(char **av, t_map *map);

#endif