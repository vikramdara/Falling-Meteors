//
// Created by vikra on 5/1/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_PLAYER_H
#define FINALPROJECT_MYLIBRARY_PLAYER_H

#include <Box2D/Box2D.h>
#include <cinder/app/AppBase.h>
#include <cinder/gl/Texture.h>
#include <mylibrary/Conversion.h>

namespace mylibrary {

class Player {

 public:
  /**
   * Constructor to make a player object.
   * @param world is the world where the player body will be added to
   */
  explicit Player(b2World* world);

  /**
   * Default destructor to destroy player once game ends.
   */
  ~Player();

  /**
   * This method sets the player texture to the file path given
   * @param texture_file_path the file path that contains
   * the image of the player
   */
  void SetPlayerTexture(const std::string& texture_file_path);

  /**
   * This method is used to get the player texture
   * @return the player texture
   */
  const cinder::gl::TextureRef& GetPlayerTexture() const;

  /**
   * This is the body that all box2d mechanics will take place in.
   */
  b2Body* player_body;


  /**
   * Density of the player object
   */
  float density;

  /**
   * Size of the player
   */
  const float kPlayerRadius = 25;

 private:
  /**
   * This is the texture that the player will have in the game.
   */
  cinder::gl::TextureRef player_texture;

};

}

#endif  // FINALPROJECT_PLAYER_H
