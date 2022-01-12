#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hanoi.h"

void tower_init(tower *t, const size_t size, const size_t type)
{
    peg_init(&t->peg_a, size, type, "A");
    peg_init(&t->peg_b, size, type, "B");
    peg_init(&t->peg_c, size, type, "C");

    puts("Tower initialized");
}

void tower_rec_algo(tower *t, const size_t disks)
{
    puts("#Start");

    void *value = calloc(1, t->peg_a.type);
    rec_algo(t, disks, &t->peg_a, &t->peg_c, &t->peg_b, value);

    free(value);
    puts("#End");
}

void rec_algo(tower *t, const size_t n, peg *src, peg *trg, peg *aux, void *value)
{
    if (n>0)
    {
        rec_algo(t, n-1, src, aux, trg, value);

        peg_append(trg, peg_last_value(src, value));
        peg_remove(src);

        peg_print(&t->peg_a);
        peg_print(&t->peg_b);
        peg_print(&t->peg_c);

        rec_algo(t, n-1, aux, trg, src, value);
    }
}

void tower_iter_algo(tower *t, const size_t disks)
{
    puts("#Start");

    size_t moves = pow(2, disks) -1;

    if (disks%2)
    {
        iter_algo(t, moves, &t->peg_a, &t->peg_c, &t->peg_b);
    }
    else
    {
        iter_algo(t, moves, &t->peg_a, &t->peg_b, &t->peg_c);
    }    

    puts("#End");
}

void iter_algo(tower *t, const size_t moves, peg *src, peg *trg, peg *aux)
{
    void *v1 = calloc(1, t->peg_a.type);
    void *v2 = calloc(1, t->peg_a.type);

    for (size_t i=1; i<=moves; i++)
    {
        switch(i%3)
        {
            case(0):
            move_disk_between(aux, trg, v1, v2);
            break;

            case(1):
            move_disk_between(src, trg, v1, v2);
            break;

            case(2):
            move_disk_between(src, aux, v1, v2);
            break;
        }

        peg_print(&t->peg_a);
        peg_print(&t->peg_b);
        peg_print(&t->peg_c);
    }

    free(v1);
    free(v2);
}

void move_disk_between(peg *p1, peg *p2, void *v1, void* v2)
{
    if (peg_empty(p1))
    {
        peg_append(p1, peg_last_value(p2, v2));
        peg_remove(p2);
        return;
    }

    if (peg_empty(p2))
    {
        peg_append(p2, peg_last_value(p1, v1));
        peg_remove(p1);
        return;
    }

    if (pegs_compare(p1, p2, v1, v2)>0)
    {
        peg_append(p1, peg_last_value(p2, v2));
        peg_remove(p2);
        return;
    }

    if (pegs_compare(p1, p2, v1, v2)<0)
    {
        peg_append(p2, peg_last_value(p1, v2));
        peg_remove(p1);
        return;
    }
}

int pegs_compare(peg *p1, peg *p2, void *v1, void *v2)
{
    int res = memcmp(peg_last_value(p1, v1), peg_last_value(p2, v2), p1->type);
    return res;
}

void peg_init(peg *p, const size_t size, const size_t type, const char *name)
{
    p->data = calloc(size, type);

    p->count = 0;
    p->type = type;
    p->size = size;
    p->name = name;

    puts("Peg initialized");
}

int peg_append(peg *peg, void *value)
{
    if (peg->count>=peg->size)
    {
        puts("Full peg");
        return -1;
    } 

    size_t offset = peg->count * peg->type;
    peg->data[offset] = *(uint8_t*)value;
    peg->count++;

    puts("Disc added");
    return 0;
}

int peg_remove(peg *peg)
{
    if (!peg_empty(peg))
    {
        peg->count--;

        puts("Disc removed");
        return 0;
    }

    return -1;
}

void peg_print(peg *p)
{
    int val;

    printf("%s = [", p->name);
    for (size_t i=0; i<p->count; i++)
    {
        peg_index_value(p, i, &val);
        printf("%d, ", val);
    }
    puts("]");
}

void *peg_last_value(peg *p, void *value)
{
    peg_index_value(p, p->count-1, value);
    return value;
}

int peg_index_value(peg *p, const size_t index, void *value)
{
    if (index>=p->count) 
    {
        puts("Invalid index");
        return -1;
    }

    size_t offset = index * p->type;
    memcpy(value, p->data + offset, p->type);
    return 0;
}

int peg_empty(peg *p)
{
    if (p->count>0)
    {
        return 0;
    }

    puts("Empty peg");
    return -1;
}