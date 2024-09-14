#include "Game.h"

Game::~Game()
{

}

bool Game::Initialize()
{
    GameEngine* pGameEngine = GameEngine::GetEngine();

    pGameEngine->setFrameRate(30);

    return true;
}

void Game::Start()
{
    srand(time(NULL));

    GameEngine* pGE = GameEngine::GetEngine();
    SDL_Renderer *renderer = pGE->GetRenderer();

    _pForestBitmap = new Bitmap(renderer, "res/Forest.bmp");
    SDL_Color scTransColor = { 0xFF, 0x0, 0xFF};
    _pGolfBallBitmap = new Bitmap(renderer, "res/GolfBall.bmp", &scTransColor);

    SDL_Rect rcBounds = {0, 0, 600, 400};
    _pGolfBallSprite[0] = new Sprite(_pGolfBallBitmap, rcBounds);
    _pGolfBallSprite[1] = new Sprite(_pGolfBallBitmap, rcBounds, BA_WRAP);
    _pGolfBallSprite[2] = new Sprite(_pGolfBallBitmap, rcBounds, BA_BOUNCE);
    _pGolfBallSprite[0]->SetVelocity(2, 1);
    _pGolfBallSprite[1]->SetVelocity(3, 2);
    _pGolfBallSprite[2]->SetVelocity(7, 4);

    _bDragging = false;
    _iDragBall = -1;
}

void Game::End()
{
    delete _pForestBitmap;
    delete _pGolfBallBitmap;
    for(int i=0; i<3; i++)
    delete _pGolfBallSprite[i];
    GameEngine* pGameEngine = GameEngine::GetEngine();
    delete pGameEngine;
}

void Game::Activate()
{
  
}

void Game::Deactivate()
{

}

void Game::Paint()
{
    GameEngine* pGameEngine = GameEngine::GetEngine();
    SDL_Renderer *renderer = pGameEngine->GetRenderer();
    _pForestBitmap->Draw(renderer, 0, 0);
    for(int i=0; i<3; i++)
    _pGolfBallSprite[i]->Draw(renderer);
    SDL_RenderPresent(renderer);
}

void Game::Cycle()
{
    for(int i=0; i<3; i++)
    _pGolfBallSprite[i]->Update();
}

void Game::HandKeys()
{
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_GetScancodeFromKey(SDLK_q)])
    {
        exit(0);
    }
}

void Game::MouseButtonDown(int x, int y, bool bLeft)
{
    if(bLeft && !_bDragging)
    {
        for(int i=0; i<3; i++)
        if(_pGolfBallSprite[i]->IsPointInside(0, 0))
        {
            _bDragging = true;
            _iDragBall = i;
         #ifndef DEBUG
            printf("dragging ball %\n", i);
         #endif
            MouseMove(x, y);
            break;      
        }
    }
}


void Game::MouseButtonUp(int x, int y, bool bLeft)
{

            _bDragging = false;
         #ifndef DEBUG
            std::cout << "stoped dragging" << std::endl;
         #endif
}


void Game::MouseMove(int x, int y)
{
    if(_bDragging)
    {
         #ifndef DEBUG
            printf("move ball %d to %d %d\n", _iDragBall, 
                        x-(_pGolfBallBitmap->GetWidth()/2),
                        y-(_pGolfBallBitmap->GetHeight()/2));
         #endif
            _pGolfBallSprite[_iDragBall]->SetPosition(x-(_pGolfBallBitmap->GetWidth()/2),
                        y-(_pGolfBallBitmap->GetHeight()/2)) ;     
        
    }
}

