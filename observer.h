#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Subject;

class Observer {
  public:
    void notify(Subject &whoFrom);
};

#endif
