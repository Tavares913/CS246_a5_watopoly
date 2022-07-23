#include <vector>
#include "subject.h"

// TODO add observer file
void Subject::notifyObservers() {
    for (auto &ob : observers) {
        ob->notify(*this);
    }
}

void Subject::attach(Observer *ob) {
    observers.emplace_back(ob);
}