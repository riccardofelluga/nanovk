#include <iostream>

#include "nanovk/view.h"

int main(int argc, char** argv){
    auto view = nanovk::View("nanovk", 1200, 800);
    view.render();
    return 0;
}