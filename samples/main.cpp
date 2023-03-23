#include <iostream>
#include <memory>

#include "nanovk/device.h"
#include "nanovk/window.h"
#include "nanovk/runtime.h"

int main(int argc, char** argv) {

  auto window = nanovk::Window::Create("NanoVK test", 1200, 800);
  
  auto app = nanovk::Runtime::CreateWithExtensions("nanovk test", window->GetWindowExtensions());

  auto surface = window->GetSurface(app->GetInstance());

  auto draw = [&](){
    std::cout << "Window is open!\n";
    return;
  };

  window->OpenWindowAndLoop(draw);
  return 0;
}

