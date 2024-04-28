#define _ESAT_BACKEND 1
// #include "sprite.h"
#include "gsprite.h"

#include "animationinstance.h"

Sprite::Sprite(Texture& texture, Vec2 origin, Vec2 size) {
  type_ = EntityType_Sprite;
  handle_ = esat::SubSprite(texture.handle_, (int)origin.x, (int)origin.y, (int)size.x, (int)size.y);
}

Sprite::Sprite(Texture& texture, int x, int y, int w, int h){
  type_ = EntityType_Sprite;
  handle_ = esat::SubSprite(texture.handle_, (int)x, (int)y, (int)w, (int)h);
}

Sprite::Sprite(const Sprite& other){
  type_ = EntityType_Sprite;
  handle_ = esat::SubSprite(other.handle_, 0, 0, 
                            other.width(), 
                            other.height());
}

Sprite::~Sprite() {
  if (nullptr != handle_) {
    release();
  }
}

void Sprite::release() {
  if (nullptr != handle_) {
    esat::SpriteRelease(handle_);
    handle_ = nullptr;
  }
}

void Sprite::init(Texture &texture, const int x, const int y, const int w, const int h) {
  if (nullptr != handle_) {
    release();
  }

  handle_ = esat::SubSprite(texture.handle_, x, y, w, h);
}

int Sprite::width() const {
  return esat::SpriteWidth(handle_);
}

int Sprite::height() const {
  return esat::SpriteHeight(handle_);
}

void Sprite::draw() const {
  if (enabled_) {
    if (nullptr == handle_)
      return;

    esat::DrawSpriteWithMatrix(handle_, transform_.calculateMatrix().m);
  }
}
