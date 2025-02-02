#include "Subject.h"


void Subject::addObserver(IObserver* observer) {
    observers.push_back(observer);
}



