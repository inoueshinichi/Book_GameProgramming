//
//  PauseMenu.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/29.
//

#ifndef PauseMenu_hpp
#define PauseMenu_hpp

#include "UIScreen.hpp"

class PauseMenu final : public UIScreen
{
public:
    PauseMenu(class Game* game);
    ~PauseMenu();
    
    void HandleKeyPress(int key);
};

#endif /* PauseMenu_hpp */
