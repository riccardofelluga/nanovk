#include <iostream>

#include "nanovk/device.h"
#include "nanovk/runtime.h"

int main(int argc, char** argv) {
  auto app = nanovk::Runtime("nanovk test");

  auto device = app.GetDevice(nanovk::DeviceType::GPU); 

  //const auto& stream = device.CreateStream(nanovk::StreamType::Graphics);

  //app.Subscribe(stream);

  app.Loop();

  return 0;
}

