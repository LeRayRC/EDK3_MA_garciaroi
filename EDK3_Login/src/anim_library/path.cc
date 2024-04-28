
#include "path.h"
#include "math_lib/vector_2.h"

#include "animationinstance.h"

Path::Path() {
  type_ = EntityType_Path;
  border_color_ = Color(255, 255, 255,255);
  fill_color_ = Color(0, 0, 0,255);
}

Path::Path(const Color border, const Color fill, const bool solid, const Vec2 *vertexes, const int n_vertexes) {
  border_color_ = border;
  fill_color_ = fill;
  solid_ = solid;
  for (int i = 0; i < n_vertexes; i++) {
    vertexes_.push_back(vertexes[i]);
  }
  type_ = EntityType_Path;
}

Path::~Path() {}

void Path::set_border_color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) {
  border_color_.red_ = r;
  border_color_.green_ = g;
  border_color_.blue_ = b;
  border_color_.alpha_ = a;
}

void Path::set_fill_color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) {
  fill_color_.red_ = r;
  fill_color_.green_ = g;
  fill_color_.blue_ = b;
  fill_color_.alpha_ = a;
}

void Path::set_solid(const bool solid) {
  solid_ = solid;
}

void Path::addVertex(const Vec2 new_vertex) {
  vertexes_.push_back(new_vertex);
}

int Path::getSize() const {
  return (int)vertexes_.size();
}

void Path::InitRegularPolygon(const int vertexes) {
  // Mat3 model;
  float step = 6.28f / vertexes;

  Vec2 temp;
  for (int i = 0; i < vertexes; i++) {
    temp.x = (float)cos(step * i);
    temp.y = (float)sin(step * i);
    vertexes_.push_back(temp);
  }
}

void Path::print() {
  for (int i = 0; i < vertexes_.size(); i++) {
    printf("regular vertex #%d: {%f, %f} \n", i, vertexes_[i].x, vertexes_[i].y);
  }

  for (int i = 0; i < vertexes_transformed_.size(); i++) {
    printf("transformed vertex #%d: {%f, %f} \n", i, vertexes_transformed_[i].x, vertexes_transformed_[i].y);
  }
}

void Path::update() {
  if (enabled_ && play_animation_) {
    if (nullptr != anim_instance_) {
      anim_instance_->update();
      if (anim_instance_->isEnded()) {
        stopAnimation();
        // delete anim_instance_;
        // anim_instance_ = nullptr;
      }
    }

    transform_.transformPoints(vertexes_, vertexes_transformed_);
  }
}
