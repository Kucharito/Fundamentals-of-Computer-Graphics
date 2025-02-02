#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <vector>
#include "IObserver.h"
#include <glm/glm.hpp>

class Subject {
public:
    void addObserver(IObserver* observer);
    virtual void notifyObservers()=0;


protected:
    std::vector<IObserver*> observers;
};
