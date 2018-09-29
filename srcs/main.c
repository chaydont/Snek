/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaydont <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:47:44 by chaydont          #+#    #+#             */
/*   Updated: 2018/09/10 15:32:03 by chaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/snek.h"

t_map	*initialize(SDL_Renderer *ren)
{
	t_map	*map;
	int		i;

	i = 0;
	map = (t_map*)malloc(sizeof(t_map));
	map->size = INITIAL_LENGTH;
	map->head.x = 5;
	map->head.y = 5;
	map->dir = RIGHT;
	map->seed = rand();
	srand(map->seed);
	while (i < MAP_WIDTH)
		bzero(map->grid[i++], MAP_LENGTH * sizeof(int));
	new_apple(map);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);
	return (map);
}

int		main()
{
	srand(time(NULL));
	SDL_Window		*win;
	SDL_Event		event;
	SDL_Renderer	*ren;
	SDL_bool		quit;
	t_map			*map;
	enum e_dir		temp;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(MAP_WIDTH * SQUARE + GAP,
		MAP_LENGTH * SQUARE + GAP, SDL_WINDOW_SHOWN, &win, &ren);

	map = initialize(ren);
	quit = SDL_FALSE;
	while (!quit)
	{
		temp = map->dir;
		while (SDL_PollEvent(&event))
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				quit = SDL_TRUE;
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				while (SDL_PollEvent(&event) && !(event.type == SDL_KEYDOWN))
					SDL_Delay(1);
			}
			else if (event.key.keysym.sym == SDLK_UP && temp != DOWN)
				map->dir = UP;
			else if (event.key.keysym.sym == SDLK_DOWN && temp != UP)
				map->dir = DOWN;
			else if (event.key.keysym.sym == SDLK_LEFT && temp != RIGHT)
				map->dir = LEFT;
			else if (event.key.keysym.sym == SDLK_RIGHT && temp != LEFT)
				map->dir = RIGHT;
		}
		map->dir = algo(map);
		if (!game(map))
		{
			SDL_Delay(2000);
			free(map);
			while (SDL_WaitEvent(&event))
			{
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					printf("Nouvelle partie !\n");
					map = initialize(ren);
					break ;
				}
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = SDL_TRUE;
					SDL_DestroyWindow(win);
					SDL_DestroyRenderer(ren);
					SDL_Quit();
					return (0);
				}
			}
		}
		display(*map, ren);
		SDL_Delay(SPEED);
	}
	free(map);
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
	return (0);
}
