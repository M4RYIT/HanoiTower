#include <stdlib.h>
#include <stdio.h>
#include "hanoi.h"

int main()
{
    size_t disks = 4;
    int n = disks;

    tower t;
    tower_init(&t, disks, sizeof(int));

    for (int i=n; i>0; i--)
    {
        peg_append(&t.peg_a, &i);
    }

    // Recursive algo
    // tower_rec_algo(&t, disks);

    // Iterative algo
    tower_iter_algo(&t, disks);

    return 0;
}