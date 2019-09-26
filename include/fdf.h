/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 10:11:20 by maginist          #+#    #+#             */
/*   Updated: 2019/09/26 15:11:45 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libprintf/include/libprintf.h"
# include <mlx.h>
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
	void			*mlx_ptr;
	void			*wind;
	char			*name;
    int				max_x;
	int				max_y;
	int				x1;
	int				y1;
	int				dx;
	int				dy;
	int				dp;
	int				e;
	int				ne;
	int				error;
	int				scale;
	int				move_x;
	int				move_y;
	t_stock			*stock;
}					t_map;

int				main(int ac, char **av);
int				parsing_arg(char **av, t_map *map);
void			run_fdf(t_map *map);

#endif