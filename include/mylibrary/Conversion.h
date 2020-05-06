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
  constexpr static const float METERS_TO_POINTS = 200.0f;
  constexpr static float POINTS_TO_METERS = 0.005f;

  static float MetersToPoints( float var )			{ return var * METERS_TO_POINTS; }
  static cinder::vec2 metersToPoints( const cinder::vec2 &var )	{ return var * METERS_TO_POINTS; }
  static float pointsToMeters( float var )			{ return var * POINTS_TO_METERS; }
  static cinder::vec2 pointsToMeters( const cinder::vec2 &var )	{ return var * POINTS_TO_METERS; }
  static b2Vec2 pointsToMeters( const b2Vec2 &var )	{ return POINTS_TO_METERS * var; }
};


}


#endif  // FINALPROJECT_MYLIBRARY_CONVERSION_H
