/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 10:11:20 by maginist          #+#    #+#             */
/*   Updated: 2019/08/22 18:26:11 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libprintf/include/libprintf.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>

typedef struct		s_map
{
    int				**grid;
	unsigned char	**color;
    int				max_x;
	int				max_y;
	int				error;
}					t_map;

int				main(int ac, char **av);
int				parcing_arg(char **av, t_map *map);

#endif