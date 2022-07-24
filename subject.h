#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>

class Observer;

class Subject {
    vector<Observer *> observers;

  public:
    void notifyObservers();
    void attach(Observer *);
};

#endif