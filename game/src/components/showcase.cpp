#pragma once

#include "components/showcase.h"

using namespace bs;

void CShowcase::update() {
    float rotation = mSpeed * gTime().getFrameDelta();
    SO()->rotate(mAxis, Radian(rotation));
}