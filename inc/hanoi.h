#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct peg
{
    size_t count;

    size_t type;
    size_t size;

    uint8_t *data;
    const char *name;
}
peg;

typedef struct tower
{
    peg peg_a;
    peg peg_b;
    peg peg_c;
}
tower;

void tower_init(tower *t, const size_t size, const size_t type);

void tower_rec_algo(tower *t, const size_t disks);

void rec_algo(tower *t, const size_t n, peg *src, peg *trg, peg *aux, void *value);

void tower_iter_algo(tower *t, const size_t disks);

void iter_algo(tower *t, const size_t moves, peg *src, peg *trg, peg *aux);

void move_disk_between(peg *p1, peg *p2, void *v1, void* v2);

int pegs_compare(peg *p1, peg *p2, void *v1, void *v2);

void peg_init(peg *p, const size_t size, const size_t type, const char *name);

int peg_append(peg *peg, void *value);

int peg_remove(peg *peg);

void peg_print(peg *p);

void *peg_last_value(peg *p, void *value);

int peg_empty(peg *p);

int peg_index_value(peg *p, const size_t index, void *value);