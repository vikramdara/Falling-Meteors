//
// Created by vikra on 5/1/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_METEOR_H
#define FINALPROJECT_MYLIBRARY_METEOR_H

#include <Box2D/Box2D.h>
#include <cinder/Rand.h>
#include <cinder/app/AppBase.h>
#include <cinder/gl/Texture.h>
#include <mylibrary/Conversion.h>
#include <mylibrary/Wave.h>

namespace mylibrary {

class Meteor {

 public:
  /**
   * Constructor to make a meteor object.
   * @param world is the world where the meteor body will be added to
   * @param radius is the size of the meteor
   * @param wave is the current wave the game is in. Used to set position of the
   * meteor
   * @param seconds is the amount of time elapsed since the fourth wave.
   */
  explicit Meteor(b2World* world,
      float radius,
      const mylibrary::Wave& wave,
      double seconds);

  /**
   * This method sets the meteor texture to the file path given
   * @param texture_file_path the file path that contains
   * the image of the meteor
   */
  void SetMeteorTexture(const std::string& texture_file_path);

  /**
   * This method is used to get the meteor texture
   * @return the meteor texture
   */
  const cinder::gl::TextureRef& GetMeteorTexture() const;


  /**
   * This is the body that all box2d mechanics will take place in.
   */
  b2Body* meteor_body;


 private:
  /**
   * This private method sets the starting point of the meteor if we are in wave
   * four. Wave four is 15 seconds, for the first 5 seconds the meteors will
   * come from the right. Next 5 it will come from the top, and the last 5 it
   * will come from the left.
   * @param meteor This is the box 2d body definition needed to set start
   * @param kWave is the current wave we are in to see if we even need change
   * the starting point
   * @param seconds is the number of seconds since the 4th wave started
   * @param starting_position is the position that this method will change
   * @param kCinderRadius is the radius of the meteor in cinder coordinates
   */
  void ChangeStartingPointOfMeteor(b2BodyDef& meteor,
      const mylibrary::Wave& kWave,
      double seconds,
      cinder::vec2& starting_position,
      float kCinderRadius);

  /**
   * This is the texture that the meteor will have in the game.
   */
  cinder::gl::TextureRef meteor_texture;
};

}


#endif  // FINALPROJECT_MYLIBRARY_METEOR_H
