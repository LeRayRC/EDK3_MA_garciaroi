#define _ESAT_BACKEND 1

#include "gwindow.h"

#include "game.h"

Window::Window() {}

Window::~Window() {}

void Window::windowInit(Vec2 resolution) {
  esat::WindowInit((int)resolution.x, (int)resolution.y);
}

bool Window::isOpen() {
  return esat::WindowIsOpened();
}

void Window::windowDrawBegin() {
  esat::DrawBegin();
  esat::DrawClear(0, 0, 0);
}

void Window::windowDrawEnd() {
  esat::DrawEnd();
}

void Window::windowRenderFrame() {
  esat::WindowFrame();
}

void Window::windowDestroy() {
  esat::WindowDestroy();
}