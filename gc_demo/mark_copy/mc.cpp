//
// Created by Haotao Lai on 2018-11-06.
//

#include "mc.h"

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
    pool.root->obj = p1;
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

    // when allocate space for p6, since no memory available
    // anymore, need to go one GC, during that time, p2 will
    // be free, all objects will be copied, and p2 will be
    // placed at the end in the new space
    MyObj *p6 = create_obj(6);
    alloc(&pool, p6);
    cout << "= = = = = = = = = = = =" << endl;

    MyObj *p7 = create_obj(7);
    alloc(&pool, p7);
    cout << "= = = = = = = = = = = =" << endl;

    pool.root->obj = nullptr;
    gc(&pool);
    free_obj(pool.root);

    return 0;
}