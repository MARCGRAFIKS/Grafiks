#include <SDL.h>
#include <iostream>
#include "IGame.h"
#include "Game.h"
#include "GameEngine.h"

int main(int argc, char** argv)
{
    IGame* pGame = new Game;

    GameEngine* pGameEngine = GameEngine::GetEngine();
    pGameEngine->m_game = pGame;

    const char* game_name = "Fore";
    const char* game_icon = "res/Fore_sm.ico";
    int window_width = 600;
    int window_height = 400;
    
    if(!pGameEngine->Initialize(game_name, game_icon, 
         window_width, window_height) || !pGame->Initialize())
    {
        std::cout << "INIT ERR" << std::endl;
    }  

    pGameEngine->Run();

    return EXIT_SUCCESS;   
}