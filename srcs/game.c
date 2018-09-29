/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 00:08:03 by chaydont          #+#    #+#             */
/*   Updated: 2018/06/07 19:20:47 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/snek.h"

void	new_apple(t_map *map)
{
	t_pos	apple;
	int		n;

	apple.x = 1;
	apple.y = 1;
	n = rand() % ((MAP_WIDTH - 2) * (MAP_LENGTH - 2) - map->size);
	while (n > 0 && n < (MAP_LENGTH - 2) * (MAP_WIDTH - 2) - map->size)
	{
		if (apple.x + 1 < MAP_LENGTH - 1)
			apple.x++;
		else
		{
			apple.y++;
			apple.x = 1;
		}
		if (!map->grid[apple.y][apple.x])
			n--;
	}
	map->apple = apple;
	//printf("%d %d\n", apple.x, apple.y);
}

void	snek_step(t_map *map)
{
	t_pos i;

	i.y = -1;
	if (map->head.x == map->apple.x && map->head.y == map->apple.y)
	{
		map->size++;
		new_apple(map);
	}
	else
		while (++i.y < MAP_WIDTH)
		{
			i.x = -1;
			while(++i.x < MAP_LENGTH)
				if (map->grid[i.y][i.x])
					map->grid[i.y][i.x]--;
		}
}

int		game(t_map *map)
{
	if (map->dir == DOWN)
		map->head.y++;
	else if (map->dir == UP)
		map->head.y--;
	else if (map->dir == LEFT)
		map->head.x--;
	else if (map->dir == RIGHT)
		map->head.x++;
	if (map->head.x > MAP_LENGTH - 1 || map->head.x < 0 ||
		map->head.y > MAP_WIDTH - 1 || map->head.y < 0 ||
		map->grid[map->head.y][map->head.x] > 0)
	{
		printf("Score : %d\nSeed : %d\n\n", map->size - INITIAL_LENGTH, map->seed);
		return (0);
	}
	map->grid[map->head.y][map->head.x] = map->size;
	snek_step(map);
	return (1);
}
