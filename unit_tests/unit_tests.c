#include "assert.h"
#include "stdio.h"


int main() {
    assert(1 == 1);
    printf("OK\n");
    assert(1 == 2);
    printf("NO\n");
}