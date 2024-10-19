#include <NavigationManager.hpp>
#include <TUIE.hpp>
#include <engine.hpp>
#include <iostream>
#include <sched.h>
int main() {
  TUIE TUIEcontext("first");
  if (TUIEcontext.TUIEwindow == nullptr) {
    std::cout << "Make sure you have something to draw in your root file as "
                 "the parser return nullptr"
              << std::endl;
    return 1;
  }
  Navigation navigator(TUIEcontext.TUIEwindow);
  TUIEEngine engine(navigator.View->ScreenStyle->windowHeight,
                    navigator.View->ScreenStyle->windowWidth,
                    TUIEcontext.TUIEwindow->ViewData);

  if (engine.terminate == true) {
    TUIEcontext.disableRawMode();
    std::cout << "exiting due to error in allocating space for screen pixel "
                 "cell ; error occured at the renderer"
              << std::endl;
    return 1;
  }
  engine.refresh();
  TUIEcontext.disableRawMode();
  return 0;
}
