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
  explicit Barrier(b2World* world);
  ~Barrier();

  b2Body* barrier_body;
  const float kBarrierWidth = 75;
  const float kBarrierHeight = 15;


};

}

#endif  // FINALPROJECT_MYLIBRARY_BARRIER_H
