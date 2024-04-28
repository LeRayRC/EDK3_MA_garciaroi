/**
 * @file interpolate.h
 * @author Luis Miguel Jiménez
 * @brief header file that defines all the functions related to interpolation
 */

#ifndef _INTERPOLATE_H_
#define _INTERPOLATE_H_

#define PI 3.14f

enum InterpolationType {
  InterpolationType_Linear,
  InterpolationType_ExpoEaseIn,
  InterpolationType_ExpoEaseOut,
  InterpolationType_ExpoEaseInOut,
  InterpolationType_CubicEaseIn,
  InterpolationType_CubicEaseOut,
  InterpolationType_CubicEaseInOut,
  InterpolationType_BounceEaseIn,
  InterpolationType_BounceEaseOut,
  InterpolationType_ElasticEaseIn,
  InterpolationType_ElasticEaseOut,
  InterpolationType_None,
  /*
  InterpolationType_ElasticEaseInOut
  InterpolationType_QuarticEaseIn,
  InterpolationType_QuarticEaseOut,
  InterpolationType_QuarticEaseInOut,
  InterpolationType_QuinticEaseIn,
  InterpolationType_QuinticEaseOut,
  InterpolationType_QuinticEaseInOut,
  InterpolationType_QuadraticEaseIn,
  InterpolationType_QuadraticEaseOut,
  InterpolationType_QuadraticEaseInOut,
  InterpolationType_SineEaseIn,
  InterpolationType_SineEaseOut,
  InterpolationType_SineEaseInOut,
  InterpolationType_CircularEaseIn,
  InterpolationType_CircularEaseOut,
  InterpolationType_CircularEaseInOut,
  InterpolationType_BackEaseIn,
  InterpolationType_BackEaseOut,
  InterpolationType_BackEaseInOut,
  */
};

class Interpolate{
  private:
    Interpolate();
    ~Interpolate();

    /**
     * @brief Linear interpolation between two values.
     *
     * This function performs linear interpolation between two values based on a given percentage.
     * The interpolation formula is: result = initial + ((final - initial) * percentage).
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for linear interpolation.
     */
    static float Linear(float percentage, float initial, float final);

    /**
     * @brief Exponential ease-in interpolation.
     *
     * This function applies exponential ease-in interpolation between two values based on a given percentage.
     * The interpolation formula is: result = (percentage == 0) ? 0 : pow(2, 10 * percentage - 10).
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for exponential ease-in interpolation.
     *       If the percentage is 0, the result is 0; otherwise, the result is calculated using the specified formula.
     */
    static float ExpoEaseIn(float percentage, float initial, float final);

    /**
     * @brief Exponential ease-out interpolation.
     *
     * This function applies exponential ease-out interpolation between two values based on a given percentage.
     * The interpolation formula is: result = (percentage == 1.0f) ? 1.0f : 1.0f - pow(2, -10 * percentage).
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for exponential ease-out interpolation.
     *       If the percentage is 1.0f, the result is 1.0f; otherwise, the result is calculated using the specified formula.
     */
    static float ExpoEaseOut(float percentage, float initial, float final);
    
    /**
     * @brief Exponential ease-in-out interpolation.
     *
     * This function applies exponential ease-in-out interpolation between two values based on a given percentage.
     * The interpolation formula is:
     * - If percentage is 0, the result is 0.
     * - If percentage is 1, the result is 1.
     * - If percentage is less than 0.5, the result is pow(2, 20 * percentage - 10) / 2.
     * - If percentage is greater than or equal to 0.5, the result is (2 - pow(2, -20 * percentage + 10)) / 2.
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for exponential ease-in-out interpolation.
     */
    static float ExpoEaseInOut(float percentage, float initial, float final);
    
    /**
     * @brief Cubic ease-in interpolation.
     *
     * This function applies cubic ease-in interpolation between two values based on a given percentage.
     * The interpolation formula is: result = percentage * percentage * percentage.
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for cubic ease-in interpolation.
     */
    static float CubicEaseIn(float percentage, float initial, float final);

    /**
     * @brief Cubic ease-out interpolation.
     *
     * This function applies cubic ease-out interpolation between two values based on a given percentage.
     * The interpolation formula is: result = 1 - pow(1 - percentage, 3).
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for cubic ease-out interpolation.
     */
    static float CubicEaseOut(float percentage, float initial, float final);

    /**
     * @brief Cubic ease-in-out interpolation.
     *
     * This function applies cubic ease-in-out interpolation between two values based on a given percentage.
     * The interpolation formula is:
     * - If percentage is less than 0.5, the result is 4 * percentage^3.
     * - If percentage is greater than or equal to 0.5, the result is 1 - pow(-2 * percentage + 2, 3) / 2.
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for cubic ease-in-out interpolation.
     */
    static float CubicEaseInOut(float percentage, float initial, float final);
    
    // static float QuarticEaseIn(float percentage, float initial, float final);
    // static float QuarticEaseOut(float percentage, float initial, float final);
    // static float QuarticEaseInOut(float percentage, float initial, float final);
    // static float QuinticEaseIn(float percentage, float initial, float final);
    // static float QuinticEaseOut(float percentage, float initial, float final);
    // static float QuinticEaseInOut(float percentage, float initial, float final);
    // static float QuadraticEaseIn(float percentage, float initial, float final);
    // static float QuadraticEaseOut(float percentage, float initial, float final);
    // static float QuadraticEaseInOut(float percentage, float initial, float final);
    // static float SineEaseIn(float percentage, float initial, float final);
    // static float SineEaseOut(float percentage, float initial, float final);
    // static float SineEaseInOut(float percentage, float initial, float final);
    // static float CircularEaseIn(float percentage, float initial, float final);
    // static float CircularEaseOut(float percentage, float initial, float final);
    // static float CircularEaseInOut(float percentage, float initial, float final);
    // static float BackEaseIn(float percentage, float initial, float final);
    // static float BackEaseOut(float percentage, float initial, float final);
    // static float BackEaseInOut(float percentage, float initial, float final);

    /**
     * @brief Elastic ease-in interpolation.
     *
     * This function applies elastic ease-in interpolation between two values based on a given percentage.
     * The interpolation formula is:
     * - If percentage is 0, the result is 0.
     * - If percentage is 1, the result is 1.
     * - Otherwise, the result is -pow(2, 10 * percentage - 10) * sin((percentage * 10 - 10.75) * (2 * PI / 3)).
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for elastic ease-in interpolation.
     */
    static float ElasticEaseIn(float percentage, float initial, float final);

    /**
     * @brief Elastic ease-out interpolation.
     *
     * This function applies elastic ease-out interpolation between two values based on a given percentage.
     * The interpolation formula is:
     * - If percentage is 0, the result is 0.
     * - If percentage is 1, the result is 1.
     * - Otherwise, the result is pow(2, -10 * percentage) * sin((percentage * 10 - 0.75) * (2 * PI / 3)) + 1.
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for elastic ease-out interpolation.
     */
    static float ElasticEaseOut(float percentage, float initial, float final);

    /**
     * @brief Bounce ease-in interpolation.
     *
     * This function applies bounce ease-in interpolation between two values based on a given percentage.
     * The interpolation is achieved by complementing the bounce ease-out interpolation.
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for bounce ease-in interpolation.
     */
    static float BounceEaseIn(float percentage, float initial, float final);

    /**
     * @brief Bounce ease-out interpolation.
     *
     * This function applies bounce ease-out interpolation between two values based on a given percentage.
     * The interpolation formula consists of multiple segments, each representing a bounce.
     *
     * @param percentage The interpolation percentage (should be in the range [0, 1]).
     * @param initial The initial value for interpolation.
     * @param final The final value for interpolation.
     *
     * @return The interpolated value between the initial and final values.
     *
     * @note The function assumes that the percentage is within the valid range [0, 1].
     *       Ensure that the input values and percentage are appropriate for bounce ease-out interpolation.
     */
    static float BounceEaseOut(float percentage, float initial, float final);
    // static float ElasticEaseInOut(float percentage, float initial, float final);

  public:
      /**
       * @brief Apply various easing interpolations to a given percentage.
       *
       * This function applies different easing interpolations based on the specified InterpolationType.
       * The supported interpolation types include Linear, ExpoEaseIn, ExpoEaseOut, ExpoEaseInOut,
       * CubicEaseIn, CubicEaseOut, CubicEaseInOut, BounceEaseOut, BounceEaseIn,
       * ElasticEaseIn, and ElasticEaseOut.
       *
       * @param type The InterpolationType specifying the type of easing to apply.
       * @param percentage The interpolation percentage (should be in the range [0, 1]).
       * @param initial The initial value for interpolation.
       * @param final The final value for interpolation.
       *
       * @return The interpolated value between the initial and final values based on the chosen easing type.
       *
       * @note The function assumes that the percentage is within the valid range [0, 1].
       *       Ensure that the input values and percentage are appropriate for the chosen easing type.
       */
      static float Easing(InterpolationType type, float percentage, float initial, float final);

      /**
       * @brief Get the human-readable name of an interpolation type.
       *
       * This function returns the human-readable name of a given InterpolationType.
       *
       * @param type The InterpolationType for which to get the name.
       *
       * @return A const char* representing the human-readable name of the interpolation type.
       *
       * @note If the interpolation type is not recognized, "Unknown" is returned.
       */
      static const char *GetInterpolationTypeName(InterpolationType type);
};

#endif