/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snek.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:54:05 by chaydont          #+#    #+#             */
/*   Updated: 2018/09/29 13:19:44 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNEK_H
# define SNEK_H

# include "libft.h"
# include "display.h"
# include "SDL2/SDL.h"
# include <time.h>

# define MAP_WIDTH 20
# define MAP_LENGTH 20
# define SPEED 10
# define INITIAL_LENGTH 4

typedef enum e_dir{UP, DOWN, LEFT, RIGHT} t_dir;

typedef struct	s_pos
{
	int x;
	int y;
}				t_pos;

typedef struct	s_map
{
	t_dir	dir;
	int		size;
	t_pos	head;
	t_pos	apple;
	int		grid[MAP_WIDTH][MAP_LENGTH];
	int		seed;
}				t_map;

int			game(t_map *map);
void		new_apple(t_map *map);
void		display(t_map map, SDL_Renderer *ren);
t_dir		ai(t_map *map);
t_dir		algo(t_map *map);

#endif
