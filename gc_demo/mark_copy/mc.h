//
// Created by Haotao Lai on 2018-11-06.
//

#ifndef VM_PRAC_MC_H
#define VM_PRAC_MC_H

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
    // Space is like a reference pool, it hold the references
    // to the objects (array of pointers)
    MyObj *space1[MEMORY_SIZE]{nullptr};
    MyObj *space2[MEMORY_SIZE]{nullptr};
    // current using space indicator
    char use_flag{'1'};
    MyObj **p_src{space1}, **p_dst{space2};

    // A pointer to an array of pointers, point to the currently
    // use reference pool
    MyObj **cur_space{space1};

    // Root of the program
    MyObj *root{nullptr};

    // size of the current memory pool
    int size{0};
} ReferencePool;

void gc(ReferencePool *pool) {
    cout << "< < < < < < GC > > > > > >" << endl;
    // mark process
    assert(pool->root != nullptr);
    MyObj *next = pool->root->obj;
    while (next != nullptr) {
        mark(next);
        next = next->obj;
        if (next == pool->root->obj) { break; }
    }

    // copy process
    int i = 0, j = 0;
    pool->size = 0;
    if (pool->use_flag == '1') {
        pool->p_src = pool->space1;
        pool->p_dst = pool->space2;
        pool->use_flag = '2';
        pool->cur_space = pool->p_dst;
    }
    else if (pool->use_flag == '2'){
        pool->p_src = pool->space2;
        pool->p_dst = pool->space1;
        pool->use_flag = '1';
        pool->cur_space = pool->p_dst;
    }
    else {
        assert("Reference pool space pointer failure");
    }
    assert(pool->p_src != nullptr);
    assert(pool->p_dst != nullptr);
    assert(pool->cur_space != nullptr);
    while (i < MEMORY_SIZE) {
        MyObj *tmp = pool->p_src[i];
        if (tmp == nullptr) {
            i++;
            continue;
        }
        if (!is_mark(tmp)) {
            free_obj(tmp);
        }
        else {
            unmark(tmp);
            pool->p_dst[j++] = tmp;
            pool->size += 1;
        }
        pool->p_src[i] = nullptr;
        i++;
    }
}

void alloc(ReferencePool *pool, MyObj *p_obj) {
    if (pool->size == MEMORY_SIZE) {
        gc(pool);
    }
    if (pool->size == MEMORY_SIZE) {
        cerr << "not enough memory, program exit" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        pool->cur_space[pool->size] = p_obj;
        cout << "allocate memory for object at: " << p_obj
             << " at index: " << pool->size << endl;
        pool->size += 1;
    }
}


#endif //VM_PRAC_MC_H
