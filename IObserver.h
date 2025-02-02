#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <glm/glm.hpp>

class IObserver {
public:
    //0-view
    //1-projection
    //2-light(position)
    //3-light(color)
	//4-light(attenuation)
	//5-light(direction)
	//6-cutoff
    //7-viewDirection
    //8-viewPosition
    virtual void update(int type) = 0;

};
