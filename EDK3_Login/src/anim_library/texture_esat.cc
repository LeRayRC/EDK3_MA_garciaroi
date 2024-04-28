#define _ESAT_BACKEND 1
#include "gtexture.h"

int Texture::kMaxTextures = 64;
int Texture::num_textures = 0;

Texture::Texture() {
  handle_ = nullptr;
}

Texture::~Texture() {
  if (nullptr != handle_) {
    release();
  }
  Texture::num_textures--;
}

void Texture::release() {
  if (nullptr != handle_) {
    esat::SpriteRelease(handle_);
    handle_ = nullptr;
  }
}

void Texture::init(const char *path) {
  if (nullptr != handle_) {
    release();
  }
  path_ = path;
  handle_ = esat::SpriteFromFile(path);
}

void Texture::init(int width, int height, unsigned char *data) {
  if (nullptr != handle_) {
    release();
  }
  handle_ = esat::SpriteFromMemory(width, height, data);
}

Handle Texture::getSubSprite(int x, int y, int w, int h) {
  if (nullptr != handle_) {
    return esat::SubSprite(handle_, x, y, w, h);
  } else {
    return nullptr;
  }
}

int Texture::width() const {
  if (nullptr != handle_) {
    return esat::SpriteWidth(handle_);
  } else {
    return 0;
  }
}

int Texture::height() const {
  if (nullptr != handle_) {
    return esat::SpriteHeight(handle_);
  } else {
    return 0;
  }
}

void Texture::ReleaseHandle(Handle handle) {
  if (nullptr != handle) {
    esat::SpriteRelease(handle);
  }
}
