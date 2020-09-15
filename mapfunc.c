#include "header.h"
int getmapid(int x,int y){
    return (*(map + x*MAP_H + x)).id;
};
void putmapid(int x,int y,int t){
    (*(map + x*MAP_H + x)).id=t;
}