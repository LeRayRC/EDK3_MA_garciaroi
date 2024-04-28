
#include "path.h"

#include "esat/draw.h"
#include "math_lib/vector_2.h"
// #include "esat/draw.h"

void Path::draw() const {
  if (enabled_) {
    int size = (int)vertexes_transformed_.size();
    Vec2 *tempvec2 = (Vec2 *)calloc(size + 1, sizeof(Vec2));

    if (NULL == tempvec2) {
      return;
    }

    for (int i = 0; i < size; i++) {
      tempvec2[i] = vertexes_transformed_[i];
    }
    tempvec2[size] = vertexes_transformed_[0];

    esat::DrawSetStrokeColor(border_color_.red_,
                             border_color_.green_,
                             border_color_.blue_,
                             border_color_.alpha_);
    if (solid_) {
      esat::DrawSetFillColor(fill_color_.red_,
                             fill_color_.green_,
                             fill_color_.blue_,
                             fill_color_.alpha_);
      esat::DrawSolidPath(&tempvec2[0].x, size + 1);
    } else {
      esat::DrawPath(&tempvec2[0].x, size + 1);
    }
    free(tempvec2);
  }
}