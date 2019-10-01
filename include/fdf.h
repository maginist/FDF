/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 10:11:20 by maginist          #+#    #+#             */
/*   Updated: 2019/10/01 16:17:16 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libprintf/include/libprintf.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

typedef struct		s_stock
{
	char			**data;
	int				width;
	struct s_stock	*next;
}					t_stock;

typedef struct		s_map
{
	int				alpha;
	int				beta;
	int				phi;
	int				**grid;
	int				**color;
	void			*mlx_ptr;
	void			*wind;
	void			*img;
	char			*canvas;
	int				bpp;
	int				size_line;
	int				endian;
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

int					main(int ac, char **av);
int					parsing_arg(char **av, t_map *map);
void				run_fdf(t_map *map);
void				select_seg_sens(t_map *map, int x, int y, int i);
int					free_map(t_map *map);

#endif
