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

    while (fenetre.IsOpen()){
        //nkentseu::NkEvents().PollEvents();
    }

    return 0;
}




