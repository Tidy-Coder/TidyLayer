#include <SDL2/SDL.h>

void displayError(char* functionName[]){
  fprintf(stderr, "Error with the \"%s\" function: %s", functionName, SDL_GetError());
}

SDL_bool createBestRenderer(SDL_Window* window, SDL_Renderer** renderer){
  fprintf(stderr, "===\nTrying to get the best renderer:");
  *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(*renderer == NULL){
    displayError("SDL_CreateRenderer");
    *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(*renderer == NULL){
      displayError("SDL_CreateRenderer");
      *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
      if(*renderer == NULL){
        displayError("SDL_CreateRenderer");
        return SDL_FALSE;
      }
    }
  }
  fprintf(stderr, "===");
  return SDL_TRUE;
}

int createApp(void app(SDL_Window*, SDL_Renderer*), SDL_bool onEvent(SDL_Event)){
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    displayError("SDL_Init");
    return EXIT_FAILURE;
  }

  SDL_Window* window = SDL_CreateWindow("tidy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 555, 555, SDL_WINDOW_SHOWN);
  if(window == NULL){
    return EXIT_FAILURE;
  }
  
  SDL_Renderer* renderer;
  if(createBestRenderer(&renderer) == SDL_FALSE){
    return EXIT_FAILURE;
  }
  
  app(window, renderer);
  
  SDL_Event event;
  while(SDL_TRUE){
    SDL_WaitEvent(&event);
    if(onEvent(event) == SDL_FALSE){
      break;
    }
  }
  
  SDL_Quit();
  return EXIT_SUCCESS;
}

void app(SDL_Window window, SDL_Renderer renderer){
  
}

SDL_bool event(SDL_Event){
  return SDL_TRUE;
}

int main(){
  return createApp(app, event);
}
