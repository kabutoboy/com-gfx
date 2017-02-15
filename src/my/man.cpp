#include "my/group.hpp"
#include "my/man.hpp"
#include "my/mathconst.hpp"
#include "my/sunflower.hpp"

MyMan::MyMan(float scl, float rotation, MyPoint *translation) {
  auto headShape = new MyCircle(HEAD_RADIUS);
  headShape->setPosition(0, BODY_LENGTH + HEAD_RADIUS);
  headShape->setColor(0x0000ff);

  auto bodyShape = new MyRectangle(BODY_THICKNESS, BODY_LENGTH);
  bodyShape->setPosition(0, 0.5f * BODY_LENGTH);
  bodyShape->setColor(0x0000ff);

  auto armShape11 = new MyRectangle(ARM_THICKNESS, 0.5f * ARM_LENGTH);
  armShape11->setPosition(0.1f * BODY_THICKNESS, -0.25f * ARM_LENGTH);
  armShape11->setColor(0x00ff00);
  auto armShape12 = new MyRectangle(ARM_THICKNESS, 0.5f * ARM_LENGTH);
  armShape12->setPosition(0.1f * BODY_THICKNESS, -0.25f * ARM_LENGTH);
  armShape12->setColor(0x00dd00);
  auto armShape21 = new MyRectangle(ARM_THICKNESS, 0.5f * ARM_LENGTH);
  armShape21->setPosition(-0.1f * BODY_THICKNESS, -0.25f * ARM_LENGTH);
  armShape21->setColor(0xff0000);
  auto armShape22 = new MyRectangle(ARM_THICKNESS, 0.5f * ARM_LENGTH);
  armShape22->setPosition(-0.1f * BODY_THICKNESS, -0.25f * ARM_LENGTH);
  armShape22->setColor(0xdd0000);

  auto legShape11 = new MyRectangle(LEG_THICKNESS, 0.5f * LEG_LENGTH);
  legShape11->setPosition(0.1f * BODY_THICKNESS, -0.25f * LEG_LENGTH);
  legShape11->setColor(0x00ff00);
  auto legShape12 = new MyRectangle(LEG_THICKNESS, 0.5f * LEG_LENGTH);
  legShape12->setPosition(0.1f * BODY_THICKNESS, -0.25f * LEG_LENGTH);
  legShape12->setColor(0x00dd00);
  auto legShape21 = new MyRectangle(LEG_THICKNESS, 0.5f * LEG_LENGTH);
  legShape21->setPosition(-0.1f * BODY_THICKNESS, -0.25f * LEG_LENGTH);
  legShape21->setColor(0xff0000);
  auto legShape22 = new MyRectangle(LEG_THICKNESS, 0.5f * LEG_LENGTH);
  legShape22->setPosition(-0.1f * BODY_THICKNESS, -0.25f * LEG_LENGTH);
  legShape22->setColor(0xdd0000);

  head = new MyGroup();
  head->add(headShape);
  body = new MyGroup();
  body->add(bodyShape);
  arm11 = new MyGroup();
  arm12 = new MyGroup();
  arm12->add(armShape12);
  arm11->add(armShape11);
  arm11->add(arm12);
  arm21 = new MyGroup();
  arm22 = new MyGroup();
  arm22->add(armShape22);
  arm21->add(armShape21);
  arm21->add(arm22);
  leg11 = new MyGroup();
  leg12 = new MyGroup();
  leg12->add(legShape12);
  leg11->add(legShape11);
  leg11->add(leg12);
  leg21 = new MyGroup();
  leg22 = new MyGroup();
  leg22->add(legShape22);
  leg21->add(legShape21);
  leg21->add(leg22);

  add(head);
  add(arm11);
  add(leg11);
  add(body);
  add(leg21);
  add(arm21);

  embedScale();
  embedAngle();
  embedPosition();

  arm12->translate(new MyPoint({0, -0.5f * ARM_LENGTH}));
  arm11->translate(new MyPoint({0, 0.8f * BODY_LENGTH}));
  arm22->translate(new MyPoint({0, -0.5f * ARM_LENGTH}));
  arm21->translate(new MyPoint({0, 0.8f * BODY_LENGTH}));
  leg12->translate(new MyPoint({0, -0.5f * LEG_LENGTH}));
  leg11->translate(new MyPoint({0, 0.0f * BODY_LENGTH}));
  leg22->translate(new MyPoint({0, -0.5f * LEG_LENGTH}));
  leg21->translate(new MyPoint({0, 0.0f * BODY_LENGTH}));

  translate(translation);
  rotate(rotation);
  scale(scl);
}
