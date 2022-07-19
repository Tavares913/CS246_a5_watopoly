#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include <vector>

using namespace std;

class Observer;

class Subject {

    vector<Observer *> observers;

    public:
        void notifyObservers();
        void attach(Observer *);
};

#endif