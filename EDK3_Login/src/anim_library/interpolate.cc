#include "anim_library/interpolate.h"

#include <math.h>


const char* Interpolate::GetInterpolationTypeName(InterpolationType type){
    switch (type){
    case InterpolationType::InterpolationType_Linear:
        return "Linear";
        break;
    case InterpolationType::InterpolationType_ExpoEaseIn:
        return "Ease In";
        break;
    case InterpolationType::InterpolationType_ExpoEaseOut:
        return "Ease Out";
        break;
    case InterpolationType::InterpolationType_ExpoEaseInOut:
        return "Ease InOut";
        break;
      case InterpolationType::InterpolationType_CubicEaseIn:
        return "Cubic Ease In";
        break;
      case InterpolationType::InterpolationType_CubicEaseOut:
        return "Cubic Ease Out";
        break;
      case InterpolationType::InterpolationType_CubicEaseInOut:
        return "Cubic Ease InOut";
        break;
      case InterpolationType::InterpolationType_ElasticEaseIn:
        return "Elastic Ease In";
      case InterpolationType::InterpolationType_ElasticEaseOut:
        return "Elastic Ease Out";
      case InterpolationType::InterpolationType_BounceEaseIn:
        return "Bounce Ease In";
      case InterpolationType::InterpolationType_BounceEaseOut:
        return "Bounce Ease Out";
      case InterpolationType::InterpolationType_None:
        return "None";
        break;
      default:
        return "Unknown";
        break;
      /*
      case InterpolationType_ElasticEaseInOut:
        return "Elastic Ease InOut";
      case InterpolationType_CubicEaseInOut:
        return "Cubic Ease InOut";
      case InterpolationType_QuarticEaseIn:
        return "Quartic Ease In";
      case InterpolationType_QuarticEaseOut:
        return "Quartic Ease Out";
      case InterpolationType_QuarticEaseInOut:
        return "Quartic Ease InOut";
      case InterpolationType_QuinticEaseIn:
        return "Quintic Ease In";
      case InterpolationType_QuinticEaseOut:
        return "Quintic Ease Out";
      case InterpolationType_QuinticEaseInOut:
        return "Quintic Ease InOut";
      case InterpolationType_QuadraticEaseIn:
        return "Quadratic Ease In";
      case InterpolationType_QuadraticEaseOut:
        return "Quadratic Ease Out";
      case InterpolationType_QuadraticEaseInOut:
        return "Quadratic Ease InOut";
      case InterpolationType_SineEaseIn:
        return "Sine Ease In";
      case InterpolationType_SineEaseOut:
        return "Sine Ease Out";
      case InterpolationType_SineEaseInOut:
        return "Sine Ease InOut";
      case InterpolationType_CircularEaseIn:
        return "Circular Ease In";
      case InterpolationType_CircularEaseOut:
        return "Circular Ease Out";
      case InterpolationType_CircularEaseInOut:
        return "Circular Ease InOut";
      case InterpolationType_BackEaseIn:
        return "Back Ease In";
      case InterpolationType_BackEaseOut:
        return "Back Ease Out";
      case InterpolationType_BackEaseInOut:
        return "Back Ease InOut";
      */
    }
}

float Interpolate::Linear(float percentage, float initial, float final){
  return initial + (( final - initial ) * percentage);
}

float Interpolate::ExpoEaseIn(float percentage){
  return (percentage == 0) ? 0 : powf(2, 10 * percentage - 10);
}

float Interpolate::ExpoEaseOut(float percentage){
  return (percentage == 1.0f) ? 1.0f : 1.0f - powf(2, -10 * percentage);
}

float Interpolate::ExpoEaseInOut(float percentage) {
  if (0 == percentage) {
    return 0;
  } else if (1 == percentage) {
    return 1;
  } else if (percentage < 0.5) {
    return powf(2, 20 * percentage - 10) / 2;
  } else {
    return (2 - powf(2, -20 * percentage + 10)) / 2;
  }
}

float Interpolate::CubicEaseIn(float percentage){
  return percentage * percentage * percentage;
}

float Interpolate::CubicEaseOut(float percentage){
  return 1 - powf(1 - percentage, 3);
}

float Interpolate::CubicEaseInOut(float percentage){
  return (percentage < 0.5) ? 4 * percentage * percentage * percentage : 1 - powf(-2 * percentage + 2, 3) / 2;
}

float Interpolate::BounceEaseOut(float percentage){
  const float n1 = 7.5625f;
  const float d1 = 2.75f;

  if (percentage < 1 / d1) {
    return n1 * percentage * percentage;
  } else if (percentage < 2 / d1) {
    percentage -= 1.5f / d1;
    return n1 * percentage * percentage + 0.75f;
  } else if (percentage < 2.5 / d1) {
    percentage -= 2.25f / d1;
    return n1 * percentage * percentage + 0.9375f;
  } else {
    percentage -= 2.625f / d1;
    return n1 * percentage * percentage + 0.984375f;
  }
}

float Interpolate::BounceEaseIn(float percentage){
  return 1 - Interpolate::BounceEaseOut(1 - percentage);
}

float Interpolate::ElasticEaseIn(float percentage){
  const float c4 = (2 * PI) / 3;

  return (percentage == 0) ? 
          0.0f : (percentage == 1) ? 
          1.0f : -powf(2, 10 * percentage - 10) * sinf((percentage * 10 - 10.75f) * c4);
}

float Interpolate::ElasticEaseOut(float percentage){
  const float c4 = (2 * PI) / 3;

  return (percentage == 0) ?
          0.0f : (percentage == 1) ? 
          1.0f : powf(2, -10 * percentage) * sinf((percentage * 10 - 0.75f) * c4) + 1;
}

float Interpolate::Easing(InterpolationType type, float percentage, float initial, float final){
  float temp_percentage;
  switch (type) {
  case InterpolationType::InterpolationType_Linear:
    temp_percentage = percentage;
    break;
  case InterpolationType::InterpolationType_ExpoEaseIn:
    temp_percentage = Interpolate::ExpoEaseIn(percentage);
    break;
  case InterpolationType::InterpolationType_ExpoEaseOut:
    temp_percentage = Interpolate::ExpoEaseOut(percentage);
    break;
  case InterpolationType::InterpolationType_ExpoEaseInOut:
    temp_percentage = Interpolate::ExpoEaseInOut(percentage);
    break;
  case InterpolationType::InterpolationType_CubicEaseIn:
    temp_percentage = Interpolate::CubicEaseIn(percentage);
    break;
  case InterpolationType::InterpolationType_CubicEaseOut:
    temp_percentage = Interpolate::CubicEaseOut(percentage);
    break;
  case InterpolationType::InterpolationType_CubicEaseInOut:
    temp_percentage = Interpolate::CubicEaseInOut(percentage);
    break;
  case InterpolationType::InterpolationType_BounceEaseOut:
    temp_percentage = Interpolate::BounceEaseOut(percentage);
    break;
  case InterpolationType::InterpolationType_BounceEaseIn:
    temp_percentage = Interpolate::BounceEaseIn(percentage);
    break;
  case InterpolationType::InterpolationType_ElasticEaseIn:
    temp_percentage = Interpolate::ElasticEaseIn(percentage);
    break;
  case InterpolationType::InterpolationType_ElasticEaseOut:
    temp_percentage = Interpolate::ElasticEaseOut(percentage);
    break;
  default:
    temp_percentage = percentage;
    break;
  }

    return Interpolate::Linear(temp_percentage, initial, final);
}