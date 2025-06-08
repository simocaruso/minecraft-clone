//
// Created by simone on 08/06/25.
//

#ifndef MINECRAFT_SYSTEM_HPP
#define MINECRAFT_SYSTEM_HPP

enum SystemType {
    RENDERING,
};

class System {
public:
    virtual void update(int elapsed) = 0;
};


#endif //MINECRAFT_SYSTEM_HPP
