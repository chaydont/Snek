/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 11:53:07 by chaydont          #+#    #+#             */
/*   Updated: 2018/06/07 19:19:51 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/snek.h"

void	snek_tail(t_map map, SDL_Renderer *ren)
{
	t_pos i;

	i.y = -1;
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	while (++i.y < MAP_WIDTH)
	{
		i.x = -1;
		while (++i.x < MAP_LENGTH)
			if (map.grid[i.y][i.x] < 1)
			{
				SDL_Rect re = {i.x * SQUARE, i.y * SQUARE,
					SQUARE + GAP, SQUARE + GAP};
				SDL_RenderFillRect(ren, &re);
			}
	}
}

void	snek_nek(t_map map, SDL_Renderer *ren)
{
	t_pos size;
	t_pos start;

	SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
	if (map.dir == UP || map.dir == DOWN)
	{
		size.x = SNAKE;
		size.y = GAP;
		start.x = map.head.x * SQUARE + GAP;
		start.y = map.head.y * SQUARE;
	}
	else if (map.dir == RIGHT || map.dir == LEFT)
	{
		size.x = GAP;
		size.y = SNAKE;
		start.x = map.head.x * SQUARE;
		start.y = map.head.y * SQUARE + GAP;
	}
	if (map.dir == LEFT)
		start.x += SQUARE;
	if (map.dir == UP)
		start.y += SQUARE;
	SDL_Rect r = {start.x, start.y, size.x, size.y};
	SDL_RenderFillRect(ren, &r);
}

void	display(t_map map, SDL_Renderer *ren)
{
	t_pos i;

	snek_tail(map, ren);
	snek_nek(map, ren);
	SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
	i.y = -1;
	while (++i.y < MAP_WIDTH && (i.x = -1))
		while (++i.x < MAP_LENGTH)
			if (map.grid[i.y][i.x] > 0)
			{
				SDL_Rect r = {i.x * SQUARE + GAP,
					i.y * SQUARE + GAP, SNAKE, SNAKE};
				SDL_RenderFillRect(ren, &r);
			}
	SDL_SetRenderDrawColor(ren, 200, 0, 0, 0);
	SDL_Rect r = {	map.apple.x * SQUARE + GAP,
					map.apple.y * SQUARE + GAP,
					SNAKE, SNAKE};
	SDL_RenderFillRect(ren, &r);
	SDL_RenderPresent(ren);
	snek_nek(map, ren);
	/*for(int j = 0; j < MAP_WIDTH; j++)
	{
		for(int k = 0; k < MAP_LENGTH; k++)
			printf("%3d", map.grid[j][k]);
		printf("\n");
	}
	printf("\n\n");*/
}
