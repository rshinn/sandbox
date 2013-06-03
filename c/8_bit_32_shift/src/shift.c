#include <stdio.h>

#include "shift.h"

MyInt* shift(MyInt *myInt, int shift) {
    int div = shift / 8;
    int mod = shift % 8;
    ubyte *ptr;
    printf("shift: %d, div: %d, mod: %d\n", shift, div, mod);
    ptr = (ubyte *) myInt;
    for (int i = 0; i < 4; i++) {
        printf("MyInt val: %x\n", ptr[i]); 
    }
    return myInt;
}

int main() {

    printf("Hello World");

    ubyte *ptr;
    int val = 0xAABBCCDD;
    MyInt myInt;

    printf("val = %x\n", val);

    myInt.one = (ubyte) (val >> 24);
    myInt.two = (ubyte) (val >> 16);
    myInt.three = (ubyte) (val >> 8);
    myInt.four = (ubyte) (val);

    ptr = (ubyte *) &myInt;
    for (int i = 0; i < 4; i++) {
        printf("MyInt val: %x\n", ptr[i]); 
    }

    shift(&myInt, 19);


    return(0);
}
