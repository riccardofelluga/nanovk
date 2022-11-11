#include <iostream>

#include "nanovk/view.h"
#include "nanovk/device.h"

int main(int argc, char** argv) {
    auto view = nanovk::View("nanovk", 1200, 800);
	auto device = nanovk::Device(view.getProperties());



    return 0;
}