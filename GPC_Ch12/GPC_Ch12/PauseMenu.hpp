//
//  PauseMenu.hpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/04.
//

#ifndef PauseMenu_hpp
#define PauseMenu_hpp

#include "UIScreen.hpp"

class PauseMenu : public UIScreen
{
public:
    PauseMenu(class Game* game);
    ~PauseMenu();
    
    void HandleKeyPress(int key) override;
};

#endif /* PauseMenu_hpp */
