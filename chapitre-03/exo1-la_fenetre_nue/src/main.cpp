#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

/* NKENTSEU_DEFINE_APP_DATA(([](){

    nkentseu::NkAppData d{};
    d.appName = "Test_la_fenetre_nue";
    d.appVersion = "1.0.0";
    return d;
})()) */

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
        nkentseu::NkEvents().PollEvents();
    }

    return 0;
}

//5'31''92


