#include "GameEngine.h"

GameEngine* GameEngine::m_pGameEngine = NULL;

GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{

}

bool GameEngine::Initialize(const char* szTitle, const char* szIcon,
                     int iWidth, int iHeight)
{
     m_pGameEngine = this;
     m_hWindow = NULL;
     if(strlen(szTitle)>0)
     {
        strcpy(m_szTitle, szTitle);
     }

     if(strlen(szIcon)>0)
     {
        strcpy(m_szIcon, szIcon);
     }
    m_iWidth = iWidth;
    m_iHeight = iHeight;

    m_iFrameDelay = 50;
    m_bSleep = true;
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

    m_hWindow = SDL_CreateWindow(m_szTitle, SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_UNDEFINED, m_iWidth, m_iHeight, 0);
     if(!m_hWindow)
     return false;

    SDL_Surface* surface = IMG_Load(szIcon);
    SDL_SetWindowIcon(m_hWindow, surface);
    SDL_FreeSurface(surface);

    m_renderer = SDL_CreateRenderer(m_hWindow, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer); 
    return true;    
} 

void GameEngine::Run()
{
    static int iticktrigger = 0;
    int itickcount;
    bool done = false;
    this->SetSleep(false);
    m_game->Start();

    while(!done)
    {
       if(!this->GetSleep())
       {
        itickcount=SDL_GetTicks();
        if(itickcount>iticktrigger)
        {
            iticktrigger= itickcount+this->GetframeDelay();
            m_game->Cycle();
            m_game->HandKeys();
        }
       }
       this->HandleEvent();
       m_game->Paint();
    }

    m_game->End();
}

void GameEngine::HandleEvent()
{
    SDL_Event ev;
    while(SDL_PollEvent(&ev))
    {
        switch(ev.type)
        {
            case SDL_WINDOWEVENT:
            switch(ev.window.event)
            {
                case SDL_WINDOWEVENT_CLOSE:
                exit(EXIT_SUCCESS);
                break;
            }
            case SDL_MOUSEMOTION:
            m_game->MouseMove(ev.motion.x, ev.motion.y);
            break;
            case SDL_MOUSEBUTTONDOWN:
            m_game->MouseButtonDown(ev.button.x, 
                      ev.button.y, 
                      ev.button.button==SDL_BUTTON_LEFT? true:false);

        }
    }
}

