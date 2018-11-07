//
// Created by Haotao Lai on 2018-11-06.
//

#ifndef VM_PRAC_MS_H
#define VM_PRAC_MS_H

#include <assert.h>
#include "../MyObj.h"

void mark(MyObj *p_obj) {
    p_obj->mark_flag = 1;
}

void unmark(MyObj *p_obj) {
    p_obj->mark_flag = 0;
}

bool is_mark(MyObj *p_obj) {
    return p_obj->mark_flag == 1;
}

#define MEMORY_SIZE 5

typedef struct {
    MyObj *arr[MEMORY_SIZE]{nullptr};
    MyObj *root{nullptr};
    int size{0};
} ReferencePool;

void gc(ReferencePool *pool) {
    // mark process
    assert(pool->root != nullptr);
    MyObj *next = pool->root->obj;
    while (next != nullptr) {
        mark(next);
        next = next->obj;
        if (next == pool->root->obj) { break; }
    }
    // sweep process
    int i = 0;
    while (i < MEMORY_SIZE) {
        MyObj *tmp = pool->arr[i];
        if (!is_mark(tmp)) {
            free_obj(pool->arr[i]);
            pool->arr[i] = nullptr;
            pool->size -= 1;
        }
        else {
            unmark(tmp);
        }
        i++;
    }
}

void alloc(ReferencePool *pool, MyObj *p_obj) {
    if (pool->size == MEMORY_SIZE) {
        gc(pool);
    }
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        if (pool->arr[i] == nullptr) {
            pool->arr[i] = p_obj;
            pool->size += 1;
            cout << "allocate memory for object at: " << p_obj
                 << " in the index: " << i
                 << endl;
            return;
        }
    }
    cerr << "not enough memory, program exit" << endl;
    exit(EXIT_FAILURE);
}


#endif //VM_PRAC_MS_H
