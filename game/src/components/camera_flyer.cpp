#include "Scene/BsTransform.h"

#include "components/camera_flyer.h"

using namespace bs;

void CCameraFlyer::onInitialized() {
    // Create virtual buttons we'll be using for movement (assuming we registered them previously)
    mMoveForward = VirtualButton("move-forward");
    mMoveBackward = VirtualButton("move-backward");
    mMoveLeft = VirtualButton("move-left");
    mMoveRight = VirtualButton("move-right");
    mMoveUp = VirtualButton("move-up");
    mMoveDown = VirtualButton("move-down");
    mLookVertical = VirtualAxis("look-vertical");
    mLookHorizontal = VirtualAxis("look-horizontal");
}

void CCameraFlyer::update() {
    float frameDelta = gTime().getFrameDelta();

    Vector3 direction = Vector3::ZERO;
    if (gVirtualInput().isButtonHeld(mMoveForward)) direction += SO()->getTransform().getForward();
    if (gVirtualInput().isButtonHeld(mMoveBackward)) direction -= SO()->getTransform().getForward();
    if (gVirtualInput().isButtonHeld(mMoveLeft)) direction -= SO()->getTransform().getRight();
    if (gVirtualInput().isButtonHeld(mMoveRight)) direction += SO()->getTransform().getRight();
    if (gVirtualInput().isButtonHeld(mMoveUp)) direction += SO()->getTransform().getUp();
    if (gVirtualInput().isButtonHeld(mMoveDown)) direction -= SO()->getTransform().getUp();
    
    SO()->move(direction * mMoveSpeed * frameDelta);

    auto lookSpeed = mLookSpeed * frameDelta;

    float pitch = gVirtualInput().getAxisValue(mLookVertical);
    SO()->pitch(Radian(lookSpeed * pitch));

    float yaw = gVirtualInput().getAxisValue(mLookHorizontal);
    SO()->rotate(Vector3::UNIT_Y, Radian(lookSpeed * yaw));
    // SO()->yaw(Radian(lookSpeed * yaw));
}