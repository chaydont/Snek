/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 14:50:26 by chaydont          #+#    #+#             */
/*   Updated: 2018/09/11 14:38:04 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/snek.h"

int		is_empty(int square, int value)
{
	if (!square || (square > 0 && square + value < 0) || square < value)
		return (1);
	return (0);
}

t_map	*copy_grid(t_map *map)
{
	t_map	*map2;
	t_pos	i;

	i.y = -1;
	map2 = (t_map*)malloc(sizeof(t_map));
	map2->head = map->head;
	map2->apple = map->apple;
	while (++i.y < MAP_WIDTH && (i.x = -1))
		while (++i.x < MAP_LENGTH)
			map2->grid[i.y][i.x] = map->grid[i.y][i.x];
	return (map2);
}

void	one_square(t_map *map, t_pos pos, int value)
{
	if (pos.x + 1 < MAP_LENGTH && is_empty(map->grid[pos.y][pos.x + 1], value))
		map->grid[pos.y][pos.x + 1] = value;
	if (pos.x - 1 >= 0 && is_empty(map->grid[pos.y][pos.x - 1], value))
		map->grid[pos.y][pos.x - 1] = value;
	if (pos.y + 1 < MAP_WIDTH && is_empty(map->grid[pos.y + 1][pos.x], value))
		map->grid[pos.y + 1][pos.x] = value;
	if (pos.y - 1 >= 0 && is_empty(map->grid[pos.y - 1][pos.x], value))
		map->grid[pos.y - 1][pos.x] = value;
}

void	one_grid(t_map *map, int value)
{
	t_pos	i;

	i.y = -1;
	while (++i.y < MAP_WIDTH && (i.x = -1))
		while (++i.x < MAP_LENGTH)
			if (map->grid[i.y][i.x] == value)
				one_square(map, i, value - 1);
}

void	fill_grid(t_map *map, t_pos square)
{
	int		i;

	if (square.x + 1 < MAP_LENGTH && !map->grid[square.y][square.x + 1])
		map->grid[square.y][square.x + 1] = -1;
	if (square.x >= 1 && !map->grid[square.y][square.x - 1])
		map->grid[square.y][square.x - 1] = -1;
	if (square.y + 1 < MAP_WIDTH && !map->grid[square.y + 1][square.x])
		map->grid[square.y + 1][square.x] = -1;
	if (square.y >= 1 && !map->grid[square.y - 1][square.x])
		map->grid[square.y - 1][square.x] = -1;
	i = -1;
	while (abs(i) < 200)
	{
		one_grid(map, i);
		i--;
	}
	map->grid[map->head.y][map->head.x] = 0;
}

t_dir	find_dir(t_map map, t_pos apple)
{
	int i;

	i = map.grid[apple.y][apple.x];
	while (i < -1)
	{
		if (apple.x + 1 < MAP_LENGTH && map.grid[apple.y][apple.x + 1] == i + 1)
			apple.x++;
		else if (apple.x >= 1 && map.grid[apple.y][apple.x - 1] == i + 1)
			apple.x--;
		else if (apple.y + 1 < MAP_WIDTH && map.grid[apple.y + 1][apple.x] == i + 1)
			apple.y++;
		else if (apple.y >= 1 && map.grid[apple.y - 1][apple.x] == i + 1)
			apple.y--;
		i++;
		//printf("%d %d - %d %d\n", map.head.x, map.head.y, apple.x, apple.y);
	}
	if (	apple.x + 1 < MAP_LENGTH &&	!map.grid[apple.y][apple.x + 1])
		return (LEFT);
	else if (apple.x >= 1 &&			!map.grid[apple.y][apple.x - 1])
		return (RIGHT);
	else if (apple.y + 1 < MAP_WIDTH && !map.grid[apple.y + 1][apple.x])
		return (UP);
	else if (apple.y >= 1 &&			!map.grid[apple.y - 1][apple.x])
		return (DOWN);
	return (LEFT);
}

t_dir	algo(t_map *map)
{
	t_map	*map2;
	t_dir	dir;

	map2 = copy_grid(map);
	fill_grid(map2, map->head);
	//printf("%d %d\n%d %d\n", map->apple.x, map->apple.y, map->head.x, map->head.y);
	/*for(int j = 0; j < MAP_WIDTH; j++)
	{
		for(int k = 0; k < MAP_LENGTH; k++)
		{
			if (map->apple.x == k && map->apple.y == j)
				printf("%4c", 'a');
			else
				printf("% 4d", map2->grid[j][k]);
		}
		printf("\n");
	}*/
	dir = find_dir(*map2, map->apple);
	free(map2);
	//printf("%d ", LEFT);
	//printf("%d\n", dir);
	return (dir);
}
