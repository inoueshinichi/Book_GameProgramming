//
//  DialogBox.hpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/30.
//

#ifndef DialogBox_hpp
#define DialogBox_hpp

#include "UIScreen.hpp"

class DialogBox : public UIScreen
{
public:
    // Lower draw order corresponds with further back
    DialogBox(class Game* game,
              const std::string& text,
              std::function<void()> onOK);
    ~DialogBox();
};

#endif /* DialogBox_hpp */
