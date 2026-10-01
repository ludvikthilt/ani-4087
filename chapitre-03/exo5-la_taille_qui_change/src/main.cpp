#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>



// horodatage HH::MM::SS.mm
static void AfficherHorodatage(){
    using clock = std::chrono::system_clock;
    auto now = clock::now();
    std::time_t t = clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    std::tm tm{};
    localtime_s(&tm, &t);
    std::cout<< "["<<std::put_time(&tm, "%H:%M:%S")<<"."<< std::setfill('0') <<std::setw(3)<<ms.count()<< std::setfill(' ')<<"] ";
} 

//rappel appelé à chaque NkWindowResizeEvent
static void SurRedimensionnement(int& nbEvenements, int largeur, int hauteur){
    ++nbEvenements;
    AfficherHorodatage();
    std::cout<<"#"<<nbEvenements<<" : "<<largeur<<"x"<<hauteur<<std::endl;
}

int nkmain(const nkentseu::NkEntryState &state){
    nkentseu::NkWindowConfig config;
    config.title = "la fenetre nue";
    config.width = 1000;
    config.height = 720;

    
    nkentseu::NkWindow fenetre(config);

    if(!fenetre.IsValid()){
        return 1;
    }
    //int count = 0;
    bool running= true ;
    auto& stackEvent = nkentseu::NkEvents();

    // compteur d'evenements de redirection
    int nbEvenements = 0;
    
    while (running){
        nkentseu::NkEvent* event;

        while((event = stackEvent.PollEvent()) != nullptr){
            //std::cout<<"evenement reçu"<<std::endl;
            if(event->Is<nkentseu::NkWindowCloseEvent>()){
                running = false;
            }
            if(event->Is<nkentseu::NkKeyPressEvent>()){
                auto* keyEvent = static_cast<nkentseu::NkKeyPressEvent*>(event);
                if (keyEvent->GetKey() == nkentseu::NkKey::NK_ESCAPE) {
                   running = false;
                }
            }

            if(event->Is<nkentseu::NkWindowResizeEvent>()){
                auto* resizeEvent = static_cast<nkentseu::NkWindowResizeEvent*>(event);
                SurRedimensionnement(nbEvenements, resizeEvent->GetWidth(), resizeEvent->GetHeight());
                count++;

                std::cout <<"resize"<<std::endl;
        
            }
                
        }
        
    }
std::cout<<"\nNombre d'evenements : "<<nbEvenements<<std::endl;
 return 0;
   
}





