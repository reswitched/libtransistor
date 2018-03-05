#include<SDL2/SDL.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	SDL_Window *window = NULL;
	SDL_Surface *window_surface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL init failed: %s\n", SDL_GetError());
		return 1;
	}

	printf("initialized SDL\n");
	
	window = SDL_CreateWindow("n/a", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	if(window == NULL) {
		printf("window could not be created: %s\n", SDL_GetError());
		return 1;
	}

	printf("created window\n");
	
	window_surface = SDL_GetWindowSurface(window);

	if(window_surface == NULL) {
		printf("failed to create window surface\n");
		return 1;
	}
	
	printf("got window surface\n");
	
	SDL_FillRect(window_surface, NULL, SDL_MapRGBA(window_surface->format, 0x7F, 0xFF, 0x00, 0xFF));

	SDL_Rect rect;
	rect.x = 50;
	rect.y = 50;
	rect.w = 70;
	rect.h = 70;
	
	SDL_FillRect(window_surface, &rect, SDL_MapRGBA(window_surface->format, 0x00, 0x00, 0xFF, 0xFF));

	printf("filled rect\n");
	
	SDL_UpdateWindowSurface(window);

	printf("updated window surface\n");
	
	SDL_Delay(2000);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
