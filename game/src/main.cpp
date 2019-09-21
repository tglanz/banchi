#include "BsApplication.h"

#include "Platform/BsCursor.h"

#include "Scene/BsSceneObject.h"
#include "Scene/BsTransform.h"

#include "Input/BsInput.h"
#include "Input/BsVirtualInput.h"

#include "RenderAPI/BsRenderWindow.h"
#include "Renderer/BsRenderSettings.h"
#include "Renderer/BsLight.h"

#include "Material/BsMaterial.h"

#include "Resources/BsBuiltinResources.h"
#include "Resources/BsResources.h"

#include "Importer/BsImporter.h"
#include "Importer/BsTextureImportOptions.h"
#include "Importer/BsMeshImportOptions.h"

#include "Components/BsCCamera.h"
#include "Components/BsCRenderable.h"
#include "Components/BsCLight.h"
#include "Components/BsCSkybox.h"

#include "Mesh/BsMesh.h"

#include "Utility/BsShapeMeshes3D.h"

#include "components/camera_flyer.h"
#include "components/showcase.h"

using namespace bs;

void setupInput(){
    // Set up input configuration that maps virtual keys to actual hardware keys
    SPtr<InputConfiguration> inputConfig = gVirtualInput().getConfiguration();
    inputConfig->registerButton("move-forward", BC_W);
    inputConfig->registerButton("move-right", BC_D);
    inputConfig->registerButton("move-backward", BC_S);
    inputConfig->registerButton("move-left", BC_A);
    inputConfig->registerButton("move-up", BC_SPACE);
    inputConfig->registerButton("move-down", BC_LCONTROL);
    inputConfig->registerAxis("look-vertical", (int)InputAxis::MouseY);
    inputConfig->registerAxis("look-horizontal", (int)InputAxis::MouseX);
}

void setupCamera(){
    HSceneObject so = SceneObject::create("camera");

    HCamera camera = so->addComponent<CCamera>();

    HCameraFlyer cameraFlyer = so->addComponent<CCameraFlyer>();

    SPtr<RenderWindow> window = gApplication().getPrimaryWindow();

    camera->getViewport()->setTarget(window);

    so->setPosition(Vector3(5.0f, 7.0f, 10.0f));
    so->lookAt(Vector3::ZERO);

    camera->setProjectionType(ProjectionType::PT_PERSPECTIVE);
    camera->setHorzFOV(Degree(90));

    camera->setAspectRatio(1920.0f / 1080.0f);
    camera->setMSAACount(1);
}

void setupSkybox() {
    SPtr<TextureImportOptions> importOptions = TextureImportOptions::create();
    importOptions->setIsCubemap(true);
    importOptions->setCubemapSourceType(CubemapSourceType::Cylindrical);
    importOptions->setFormat(PixelFormat::PF_RGB8);
    HTexture skyTexture = gBuiltinResources().getTexture(BuiltinTexture::Black);

    HSceneObject so = SceneObject::create("skybox");
    HSkybox skybox = so->addComponent<CSkybox>();
    skybox->setTexture(skyTexture);
}

void setupLights(){
    HSceneObject so = SceneObject::create("light");
    HLight light = so->addComponent<CLight>();

    light->setType(LightType::Directional);
    light->setColor(Color::fromABGR(0xfff1daa4));
    light->setIntensity(1.0f);
}

void setupObjects(){
    HShader shader = gBuiltinResources().getBuiltinShader(BuiltinShader::Standard);
    
    HTexture texture = gImporter().import<Texture>("../../resources/dragon.png");
    HMaterial material = Material::create(shader);
    material->setTexture("gAlbedoTex", texture);

    HMesh mesh = gImporter().import<Mesh>("../../resources/dragon.fbx");


    HSceneObject so = SceneObject::create("object");
    HRenderable renderable = so->addComponent<CRenderable>();
    HShowcase showcase = so->addComponent<CShowcase>();

    renderable->setMesh(mesh);
    renderable->setMaterial(material);

    showcase->setRotation(Vector3::UNIT_Y, 0.1f);

    so->setPosition(Vector3::ZERO);
}

int main() {
    VideoMode videoMode(1920, 1024);
    bool fullscreen = true;
    String title = "puff the magic dragon";

    Application::startUp(videoMode, title, fullscreen);

    gCursor().hide();

    setupInput();
    setupCamera();
    setupSkybox();
    setupLights();
    setupObjects();

    Application::instance().runMainLoop();
    Application::shutDown();

    return 0;
}