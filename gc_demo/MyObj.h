//
// Created by Haotao Lai on 2018-11-06.
//

#ifndef VM_PRAC_MYOBJ_H
#define VM_PRAC_MYOBJ_H

#include <iostream>
using namespace std;

struct MyObj;
struct MyObj {
    int mark_flag{0};
    int ref_count{0};
    int value{0};
    MyObj *obj{nullptr};
};

// typically user don't need to call this method explicitly
void free_obj(MyObj *p_obj) {
    cout << "free the object at: " << p_obj << endl;
    delete p_obj;
}

MyObj *create_obj(int val) {
    auto *p_obj = new MyObj;
    p_obj->value = val;
    p_obj->ref_count = 1;
    cout << "create a new object at: "
         << p_obj << " with value: " << val
         << endl;
    return p_obj;
}

void show_obj(const char *name, MyObj *p) {
    if (p == nullptr) {
        cout << "nothing to show with null pointer" << endl;
    }
    else {
        cout << name << " point to -> "
             << "object at: " << p
             << ", with value: " << p->value
             << ", RC = " << p->ref_count
             << endl;
    }
}

#endif //VM_PRAC_MYOBJ_H
