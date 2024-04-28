#include "gtexture.h"

Texture *Texture::CreateTexture() {
  if (Texture::num_textures < Texture::kMaxTextures) {
    Texture *tex = new Texture();
    Texture::num_textures++;
    return tex;
  }
  return nullptr;
}

Texture *Texture::CreateTexture(const char *name) {
  if (Texture::num_textures < Texture::kMaxTextures) {
    Texture *tex = new Texture();
    tex->init(name);
    Texture::num_textures++;
    return tex;
  }
  return nullptr;
}