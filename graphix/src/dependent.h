#pragma once
#ifndef __DEPENDANT_H__
#define __DEPENDANT_H__

#include <algorithm>
#include <list>

namespace gfx{

class dependent{
    std::list<dependent*> dependencies_;

public:
    virtual ~dependent() = default;

    virtual void adjust() = 0;

    void add_dependency(dependent *dep){
        dependencies_.push_back(dep);
    }

    void remove_dependency(dependent *dep){
        auto it = std::find(
            std::begin(dependencies_),
            std::end(dependencies_),
            dep
        );

        if (it != std::end(dependencies_)){
            dependencies_.erase(it);
        }
    }

    void update(){
        adjust();
        std::for_each(std::begin(dependencies_), std::end(dependencies_),
            [](dependent *dep){
                dep->update();
            }
        );
    }
};

}

#endif // __DEPENDANT_H__
