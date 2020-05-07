//
// Created by vikra on 5/5/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_CONVERSION_H
#define FINALPROJECT_MYLIBRARY_CONVERSION_H

#include <Box2D/Box2D.h>
#include <cinder/app/App.h>


namespace mylibrary {

class Conversions {

 public:
  /**
   * These 2 constants represent the factor that is to scale the cinder
   * and box2d coordinates together
   */
  constexpr static const float kMetersToPoints = 200.0f;
  constexpr static float kPointsToMeters = 0.005f;

  constexpr static float kWindowWidth = 800.0f;
  constexpr static float kWindowHeight = 800.0f;

  /**
   * These methods either take in a vector or float and
   * convert it to either cinder or box2d coordinates
   * @return the converted float or vector
   */
  static float MetersToPoints( float var )			{ return var * kMetersToPoints; }
  static float PointsToMeters( float var )			{ return var * kPointsToMeters; }
  static cinder::vec2 PointsToMeters( const cinder::vec2 &var )	{ return var * kPointsToMeters; }
};


}


#endif  // FINALPROJECT_MYLIBRARY_CONVERSION_H
