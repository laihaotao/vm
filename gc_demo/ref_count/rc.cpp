//
// Created by Haotao Lai on 2018-11-06.
//

#include "rc.h"

void normal_example() {
    MyObj *p1 = create_obj(1);
    MyObj *p2 = create_obj(2);
    cout << "= = = = = = = = =" << endl;

    MyObj *p11;
    p11 = add_ref(p1);
    show_obj("p11", p11);
    cout << "= = = = = = = = =" << endl;

    MyObj *p12;
    p12 = add_ref(p1);
    show_obj("p12", p12);
    p12 = change_ref(p1, p2);
    show_obj("p12", p12);
    cout << "= = = = = = = = =" << endl;

    change_ref(p12, nullptr);
    change_ref(p2, nullptr);
    cout << "= = = = = = = = =" << endl;

    rm_ref(p11);
    rm_ref(p1);
    cout << "= = = = = = = = =" << endl;
}

void circular_ref_example() {
    MyObj *p1 = create_obj(1);
    MyObj *p2 = create_obj(2);

    set_obj(p1, p2);
    set_obj(p2, p1);

    change_ref(p1, nullptr);
    change_ref(p2, nullptr);

    show_obj("p1", p1);
    show_obj("p2", p2);

    // avoid memory leak
    free_obj(p1);
    free_obj(p2);
}

// ****************** Driver ************** //
int main() {
    normal_example();
    circular_ref_example();

    return 0;
}
// ************ end of Driver ************ //
