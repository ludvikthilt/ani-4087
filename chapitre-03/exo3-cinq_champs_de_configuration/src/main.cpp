#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"



int nkmain(const nkentseu::NkEntryState &state){
    nkentseu::NkWindowConfig config;
    config.title = "la fenetre nue";
    config.width = 1000;
    config.height = 720;

    config.minimizable = false; //champ 1 , commenter et décommenter en fonction du champ à utiliser
    
    //config.maximizable = false; //champ 2
    
    //config.canFullscreen = false; //champ 3
    
    //config.fullscreen = false; //champ 4
    
    //config.frame = false; //champ 5

    nkentseu::NkWindow fenetre(config);

    if(!fenetre.IsValid()){
        return 1;
    }

    while (fenetre.IsOpen()){
        nkentseu::NkEvents().PollEvents();
    }

    return 0;
}




