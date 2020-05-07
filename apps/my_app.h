// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>
#include <mylibrary/engine.h>
#include <cinder/Rand.h>
#include <cinder/audio/Voice.h>




namespace myapp {

class MyApp : public cinder::app::App {

  const float kMetersToPointsApp = 100.0f;
 public:
  MyApp();
  /**
   * All overrided methods from cinder. Setup, update, and draw do the usual.
   */
  void setup() override;
  void update() override;
  void draw() override;

  /**
   * Upon left and right key the player will move left or right. Same for mouse
   * down and drag expect the player moves in direction it is relative to
   * the cursor.
   */
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown( cinder::app::MouseEvent event ) override;
  void mouseDrag( cinder::app::MouseEvent event ) override;

 private:
  /**
   * This method draws a meteor.
   * @param meteor is the current meteor that should be drawn.
   */
  void DrawMeteor(const mylibrary::Meteor& meteor);

  /**
   * This method draws a barrier.
   */
  void DrawBarrier();

  /**
   * This method draws a player.
   */
  void DrawPlayer();

  /**
   * If the engine boolean is_game_over is true, this method will trigger
   * drawing the game over screen.
   */
  void DrawGameOver();

  /**
   * If the engine boolean is_game_over is true, this method will trigger
   * drawing the replay button
   */
  void DrawReplayButton();

  /**
   * This method draws the background of the game.
   */
  void DrawBackground();

  /**
   * This method adds logic to the drawn replay button, if the mouse is clicked
   * in the region of the button, the game resets and you can play again.
   * @param position is the position of the mouse click
   */
  void ReplayGame(const cinder::vec2& position);

  /**
   * This method draws the wave the player is currently in.
   * @param wave is the enum representing the current wave.
   */
  void DrawCurrentWave(const mylibrary::Wave& wave);

  /**
   * This method prints the passed in text on the screen. Used to draw the
   * replay button, current wave, and game over message. Method and code gotten
   * from snake project.
   */
  void PrintText(const std::string& text,
      const cinder::Color& color,
      const cinder::ivec2& size,
      const cinder::vec2& loc,
      double color_value,
      double alpha_value,
      double font_size);

  /**
   * This is the engine that is used to run the game.
   */
  mylibrary::Engine engine_;

  /**
   * This is a voice ref that represents the background music played during the
   * game
   */
  cinder::audio::VoiceRef background_music;

  /**
   * This is the voice red that represents the sound of effect of the game
   * becoming over.
   */
  cinder::audio::VoiceRef game_over_music;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
