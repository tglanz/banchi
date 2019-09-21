#pragma once

#include "Scene/BsSceneObject.h"

#include "Input/BsInput.h"
#include "Input/BsVirtualInput.h"

using namespace bs;

class CCameraFlyer : public Component {    
  private:
    float mMoveSpeed, mLookSpeed;

    VirtualButton
        mMoveForward, mMoveBackward,
        mMoveLeft, mMoveRight,
        mMoveUp, mMoveDown;

    VirtualAxis
        mLookVertical, mLookHorizontal;

    void onInitialized() override;
    void update() override;

  public:
    // Basic constructor same as above
    CCameraFlyer(const HSceneObject& parent) : Component(parent) {
        mMoveSpeed = 5.0f;
        mLookSpeed = .2f;
    }

    void setMoveSpeed(float speed) { mMoveSpeed = speed; }
    void setLookSpeed(float speed) { mLookSpeed = speed; }
};

typedef GameObjectHandle<CCameraFlyer> HCameraFlyer;