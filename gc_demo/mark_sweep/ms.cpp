//
// Created by Haotao Lai on 2018-11-06.
//

#include "ms.h"

int main() {
    ReferencePool pool;

    // set the root
    MyObj *p0 = create_obj(0);
    pool.root = p0;

    // fill out the memory pool
    MyObj *p1 = create_obj(1);
    MyObj *p2 = create_obj(2);
    MyObj *p3 = create_obj(3);
    MyObj *p4 = create_obj(4);
    MyObj *p5 = create_obj(5);
    alloc(&pool, p1);
    alloc(&pool, p2);
    alloc(&pool, p3);
    alloc(&pool, p4);
    alloc(&pool, p5);
    p0->obj = p1;
    cout << "= = = = = = = = = = = =" << endl;

    // set the references as follows:
    // (the object p2 pointed to can be collected, no coming reference)
    //      - - - - - - - - - -
    //      |                 |
    //      v                 |
    //      p1 -> p3 -> p4 -> p5
    //       ^     ^
    //       |     |
    //      root   p2

    p1->obj = p3;
    p2->obj = p3;
    p3->obj = p4;
    p4->obj = p5;
    p5->obj = p1;

    // p6 should be placed into the space where p2 used to be
    MyObj *p6 = create_obj(6);
    alloc(&pool, p6);
    MyObj *p7 = create_obj(7);
    alloc(&pool, p7);

    cout << "= = = = = = = = = = = =" << endl;
    p0->obj = nullptr;
    free_obj(p0);
    gc(&pool);
}