#include "header.h"

void dtile(TILE t){
    attr_set(t.a,t.cp,NULL);
    addch(t.c);
}
