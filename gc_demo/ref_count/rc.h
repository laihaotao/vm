//
// Created by Haotao Lai on 2018-11-06.
//

#ifndef VM_PRAC_RC_H
#define VM_PRAC_RC_H

#include "../MyObj.h"

MyObj *add_ref(MyObj *p_old) {
    p_old->ref_count += 1;
    cout << "[RC + 1] " << "object at: " << p_old << endl;
    return p_old;
}

MyObj *change_ref(MyObj *p_old, MyObj *p_new) {
    p_old->ref_count -= 1;
    cout << "[RC - 1] " << "object at: " << p_old << endl;
    if (p_old->ref_count == 0) {
        free_obj(p_old);
    }
    if (p_new != nullptr) {
        p_new->ref_count += 1;
    }
    return p_new;
}

void set_obj(MyObj *p_host, MyObj *p_client) {
    if (p_host != nullptr && p_client != nullptr) {
        p_host->obj = p_client;
        p_client->ref_count += 1;
        cout << "[RC + 1] " << "object at: " << p_client << endl;
    }
}

void rm_ref(MyObj *p_obj) {
    change_ref(p_obj, nullptr);
}

#endif //VM_PRAC_RC_H
