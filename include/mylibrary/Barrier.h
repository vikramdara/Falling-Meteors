//
// Created by vikra on 5/6/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_BARRIER_H
#define FINALPROJECT_MYLIBRARY_BARRIER_H

#include <Box2D/Box2D.h>
#include <mylibrary/Conversion.h>


namespace mylibrary {

class Barrier {

 public:
  /**
   * Constructor to make a Barrier object.
   * @param world is the world where the player body will be added to
   */
  explicit Barrier(b2World* world);

  /**
   * Default destructor to destroy player once game ends.
   */
  ~Barrier();

  /**
   * This is the body that all box2d mechanics will take place in.
   */
  b2Body* barrier_body;

  /**
   * These the dimensions of the barrier.
   */
  const float kBarrierWidth = 75;
  const float kBarrierHeight = 15;


};

}

#endif  // FINALPROJECT_MYLIBRARY_BARRIER_H
