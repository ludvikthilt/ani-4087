#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"



int nkmain(const nkentseu::NkEntryState &state){
    nkentseu::NkWindowConfig config;
    config.title = "la fenetre nue";
    config.width = 1000;
    config.height = 720;

    
    nkentseu::NkWindow fenetre(config);

    if(!fenetre.IsValid()){
        return 1;
    }
    bool running= true ;
    auto& stackEvent = nkentseu::NkEvents();
    while (running){
        nkentseu::NkEvent* event;

        while((event = stackEvent.PollEvent()) != nullptr){
            if(event->Is<nkentseu::NkWindowCloseEvent>()){
                running = false;
            }
            if(event->Is<nkentseu::NkKeyPressEvent>()){
                auto* keyEvent = static_cast<nkentseu::NkKeyPressEvent*>(event);
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_ESCAPE) {
                   running = false;
                }
                
        }
        
    }

   
}
 return 0;
}



