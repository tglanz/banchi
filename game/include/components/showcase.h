#include "Scene/BsSceneObject.h"

using namespace bs;

class CShowcase : public Component {

  private:
    Vector3 mAxis;
    float mSpeed;

    void update() override;
    
  public:
    CShowcase(const HSceneObject& parent) : Component(parent) {
        mAxis = Vector3::ZERO;
        mSpeed = .0f;
    }
    
    void setRotation(Vector3 axis, float speed){
        mAxis = axis;
        mSpeed = speed;
    }    
};

typedef GameObjectHandle<CShowcase> HShowcase;
