#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNM/Method.hpp"
#include "BNM/MethodBase.hpp"
#include "BNM/Field.hpp"
#include "BNM/FieldBase.hpp"
#include "BNM/UnityStructures/Color.hpp"
#include "BNM/UnityStructures/Quaternion.hpp"
#include "BNM/UnityStructures/Raycasthit.hpp"
#include "BNM/UnityStructures/Vector2.hpp"
#include "BNM/UnityStructures/Vector3.hpp"
#include "BNM/UnityStructures.hpp"
#include "BNM/BasicMonoStructures.hpp"
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNMResolve.hpp"
#include <BNM/BasicMonoStructures.hpp>
#include <BNM/Class.hpp>
#include <BNM/ClassesManagement.hpp>
#include <BNM/ComplexMonoStructures.hpp>
#include <BNM/Coroutine.hpp>
#include <BNM/DebugMessages.hpp>
#include <BNM/Defaults.hpp>
#include <BNM/Delegates.hpp>
#include <BNM/Event.hpp>
#include <BNM/EventBase.hpp>
#include <BNM/EventBase.hpp>
#include <BNM/Exceptions.hpp>
#include <BNM/Field.hpp>
#include <BNM/FieldBase.hpp>
#include <BNM/Il2CppHeaders.hpp>
#include <BNM/Image.hpp>
#include <BNM/Loading.hpp>
#include <BNM/Method.hpp>
#include <BNM/MethodBase.hpp>
#include <BNM/Operators.hpp>
#include <BNM/Property.hpp>
#include <BNM/PropertyBase.hpp>
#include <BNM/UnityStructures.hpp>
#include <BNM/Utils.hpp>
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNM/Method.hpp"
#include "BNM/MethodBase.hpp"
#include "BNM/Field.hpp"
#include "BNM/FieldBase.hpp"
#include "BNM/UnityStructures/Color.hpp"
#include "BNM/UnityStructures/Quaternion.hpp"
#include "BNM/UnityStructures/Raycasthit.hpp"
#include "BNM/UnityStructures/Vector2.hpp"
#include "BNM/UnityStructures/Vector3.hpp"
#include "BNM/UnityStructures.hpp"
#include "BNM/BasicMonoStructures.hpp"
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNMResolve.hpp"
#include <BNM/BasicMonoStructures.hpp>
#include <BNM/Class.hpp>
#include <BNM/ClassesManagement.hpp>
#include <BNM/ComplexMonoStructures.hpp>
#include <BNM/Coroutine.hpp>
#include <BNM/DebugMessages.hpp>
#include <BNM/Defaults.hpp>
#include <BNM/Delegates.hpp>
#include <BNM/Event.hpp>
#include <BNM/EventBase.hpp>
#include <BNM/EventBase.hpp>
#include <BNM/Exceptions.hpp>
#include <BNM/Field.hpp>
#include <BNM/FieldBase.hpp>
#include <BNM/Il2CppHeaders.hpp>
#include <BNM/Image.hpp>
#include <BNM/Loading.hpp>
#include <BNM/Method.hpp>
#include <BNM/MethodBase.hpp>
#include <BNM/Operators.hpp>
#include <BNM/Property.hpp>
#include <BNM/PropertyBase.hpp>
#include <BNM/UnityStructures.hpp>
#include <BNM/Utils.hpp>
#include <XRInput.hpp>
#include <Mods.hpp>
#include <BNMResolve.hpp>
#include <GorillaLocomotion.hpp>
#include "cmath"

bool leftCooldown;
bool rightCooldown;
Object* leftPlatform;
Object* rightPlatform;

GameObject* leftPlat;
GameObject* rightPlat;

void Movement::Init() {

}

void Movement::Platforms() {
    bool leftGrip = XRInput::GetFloatFeature(FloatFeature::Grip, Controller::Left) > 0.5f;
    bool rightGrip = XRInput::GetFloatFeature(FloatFeature::Grip, Controller::Right) > 0.5f;

    GameObject* leftHandController = GameObject::Find("LeftHand Controller");
    GameObject* rightHandController = GameObject::Find("RightHand Controller");

    if (leftGrip && !leftCooldown) {
        leftCooldown = true;
        leftPlat = GameObject::CreatePrimitive(PrimitiveType::Cube);
        leftPlat->GetTransform()->SetPosition(leftHandController->GetTransform()->GetPosition() - Vector3(0, .1f, 0));
        leftPlat->GetTransform()->SetLocalScale(Vector3(.4f, .01f, .4f));
    }
    if (!leftGrip && leftCooldown) {
        leftCooldown = false;
        leftPlat->AddComponent(Rigidbody::GetType());
        GameObject::Destroy(leftPlat->GetComponent(Collider::GetType()));
        GameObject::Destroy(leftPlat, 5.0f);
        leftPlat = nullptr;
    }

    if (rightGrip && !rightCooldown) {
        rightCooldown = true;
        rightPlat = GameObject::CreatePrimitive(PrimitiveType::Cube);
        rightPlat->GetTransform()->SetPosition(rightHandController->GetTransform()->GetPosition() - Vector3(0, .1f, 0));
        rightPlat->GetTransform()->SetLocalScale(Vector3(.4f, .01f, .4f));
    }
    if (!rightGrip && rightCooldown) {
        rightCooldown = false;
        rightPlat->AddComponent(Rigidbody::GetType());
        GameObject::Destroy(rightPlat->GetComponent(Collider::GetType()));
        GameObject::Destroy(rightPlat, 5.0f);
        rightPlat = nullptr;
    }

    if (leftPlat && leftPlat->Alive()) {
        reinterpret_cast<Renderer*>(leftPlat->GetComponent(Renderer::GetType()))->GetMaterial()->SetColor(Color::red);
    }
    if (rightPlat && rightPlat->Alive()) {
        reinterpret_cast<Renderer*>(rightPlat->GetComponent(Renderer::GetType()))->GetMaterial()->SetColor(Color::red);
    }
}

Vector3 oldScale = Vector3(0, 0, 0);


void Movement::LongArms() {
    GameObject* gorillaPlayer = GameObject::Find(BNM_OBFUSCATE("GorillaPlayer"));
    if (oldScale == Vector3(0, 0, 0)) {
        oldScale = gorillaPlayer->GetTransform()->GetLocalScale();
    }

    switch (armIndex) {
        case 0: {
            armMult = 1.2f;
            break;
        }
        case 1: {
            armMult = 1.25f;
            break;
        }
        case 3: {
            armMult = 1.3f;
            break;
        }
        case 4: {
            armMult = 1.4f;
            break;
        }
        case 5: {
            armMult = 1.5f;
            break;
        }
        default:
            break;
    }

    gorillaPlayer->GetTransform()->SetLocalScale(Vector3(armMult, armMult, armMult));
}

void Movement::FixLongArms() {
    GameObject* gorillaPlayer = GameObject::Find(BNM_OBFUSCATE("GorillaPlayer"));
    gorillaPlayer->GetTransform()->SetLocalScale(oldScale);
}

bool lastInput;

void Movement::NoClip() {
    static Class MeshCollider = Class(O("UnityEngine"), O("MeshCollider"));
    static Property<bool> enabled = MeshCollider.GetProperty(O("enabled"));

    bool newInput = XRInput::GetBoolFeature(BoolFeature::SecondaryButton, Controller::Right);
    if (newInput != lastInput) {
        for (auto i : GameObject::FindObjectsOfType(MeshCollider.GetMonoType())->ToVector()) {
            enabled[i] = !XRInput::GetBoolFeature(BoolFeature::SecondaryButton, Controller::Right);
        }
    }
    lastInput = newInput;
}

void Movement::ExcelFly() {
    static Transform* leftHandTransform = GorillaLocomotion::Player::get_Instance()->GetLeftHandTransform();
    static Transform* rightHandTransform = GorillaLocomotion::Player::get_Instance()->GetRightHandTransform();
    static Rigidbody* rb = GorillaLocomotion::Player::get_Instance()->GetPlayerRigidBody();

    if (XRInput::GetBoolFeature(BoolFeature::PrimaryButton, Controller::Right)) {
        rb->SetVelocity(rb->GetVelocity() + (rightHandTransform->GetRight() / 2.0f));
    }

    if (XRInput::GetBoolFeature(BoolFeature::PrimaryButton, Controller::Left)) {
        rb->SetVelocity(rb->GetVelocity() + (-leftHandTransform->GetRight() / 2.0f));
    }
}

void Movement::ForceTagFreeze() {
    GorillaLocomotion::Player::get_Instance()->SetDisableMovement(true);
}

void Movement::NoTagFreeze() {
    GorillaLocomotion::Player::get_Instance()->SetDisableMovement(false);
}

void Movement::PSA() {
    if (XRInput::GetBoolFeature(BoolFeature::PrimaryButton, Controller::Right)) {
        Transform* bct = GorillaLocomotion::Player::get_Instance()->GetBodyCollider()->GetTransform();
        Transform* pt = GorillaLocomotion::Player::get_Instance()->GetTransform();

        pt->SetPosition(pt->GetPosition() + bct->GetForward() * Time::GetDeltaTime() * 5.0f);
    }
}

void Movement::Frozone() {
    bool leftGrab = XRInput::GetFloatFeature(FloatFeature::Grip, Controller::Left) > .5f;
    bool rightGrab = XRInput::GetFloatFeature(FloatFeature::Grip, Controller::Right) > .5f;

    if (leftGrab)
    {
        GameObject* slipperyPlatform = GameObject::CreatePrimitive(PrimitiveType::Cube);
        slipperyPlatform->SetName(O("Frozone"));
        reinterpret_cast<Renderer*>(slipperyPlatform->GetComponent(Renderer::GetType()))->GetMaterial()->SetColor(Color::cyan);
        slipperyPlatform->GetTransform()->SetLocalScale(Vector3(0.025f, 0.3f, 0.4f));
        slipperyPlatform->GetTransform()->SetPosition(GorillaLocomotion::Player::get_Instance()->GetLeftHandTransform()->GetPosition() + Vector3(0, -.1f, .0f));
        slipperyPlatform->GetTransform()->SetRotation(GorillaLocomotion::Player::get_Instance()->GetLeftHandTransform()->GetRotation());

        GameObject::Destroy(slipperyPlatform, 1);
    }

    if (rightGrab)
    {
        GameObject* slipperyPlatform = GameObject::CreatePrimitive(PrimitiveType::Cube);
        slipperyPlatform->SetName(O("Frozone"));
        reinterpret_cast<Renderer*>(slipperyPlatform->GetComponent(Renderer::GetType()))->GetMaterial()->SetColor(Color::cyan);
        slipperyPlatform->GetTransform()->SetLocalScale(Vector3(0.025f, 0.3f, 0.4f));
        slipperyPlatform->GetTransform()->SetPosition(GorillaLocomotion::Player::get_Instance()->GetRightHandTransform()->GetPosition() + Vector3(0, -.1f, .0f));
        slipperyPlatform->GetTransform()->SetRotation(GorillaLocomotion::Player::get_Instance()->GetRightHandTransform()->GetRotation());

        GameObject::Destroy(slipperyPlatform, 1);
    }

    GorillaLocomotion::Player::get_Instance()->GetBodyCollider()->SetEnabled(!(leftGrab || rightGrab));
}

bool lasttouchleft = false;
bool lasttouchright = false;
void Movement::PullMod() {
    if (((!GorillaLocomotion::Player::get_Instance()->IsHandTouching(true) && lasttouchleft) || (!!GorillaLocomotion::Player::get_Instance()->IsHandTouching(false) && lasttouchright)) && XRInput::GetFloatFeature(FloatFeature::Grip, Controller::Right) > .5f)
    {
        Vector3 vel = GorillaLocomotion::Player::get_Instance()->GetPlayerRigidBody()->GetVelocity();
        Transform* tran = GorillaLocomotion::Player::get_Instance()->GetTransform();
        tran->SetPosition(tran->GetPosition() + Vector3(vel.x * 2, 0.f, vel.z * 2));
    }
    lasttouchleft = GorillaLocomotion::Player::get_Instance()->IsHandTouching(true);
    lasttouchright = GorillaLocomotion::Player::get_Instance()->IsHandTouching(false);
}

Vector3 prevLeft = Vector3::zero;
Vector3 prevRight = Vector3::zero;
Vector3 veloLeft = Vector3::zero;
Vector3 veloRight = Vector3::zero;

int predInt = 1;

void Movement::VelocityLongArms() {
    static GorillaLocomotion::Player* player = GorillaLocomotion::Player::get_Instance();
    Transform* head = player->GetHeadCollider()->GetTransform();
    Transform* leftHand = player->GetLeftHandTransform();
    Transform* rightHand = player->GetRightHandTransform();

    Vector3 currentLeftOffset = head->GetPosition() - leftHand->GetPosition();
    Vector3 currentRightOffset = head->GetPosition() - rightHand->GetPosition();

    Vector3 leftVel = (currentLeftOffset - prevLeft) / Time::GetDeltaTime();
    Vector3 rightVel = (currentRightOffset - prevRight) / Time::GetDeltaTime();

    leftHand->SetPosition(leftHand->GetPosition() - leftVel * predCount);
    rightHand->SetPosition(rightHand->GetPosition() - rightVel * predCount);

    prevLeft = currentLeftOffset;
    prevRight = currentRightOffset;
}

float flySpeed = 10.f;
float oldSlideControl = -1.0f;
void Movement::SlideControl() {
    static GorillaLocomotion::Player* instance = GorillaLocomotion::Player::get_Instance();
    if (oldSlideControl == -1.0f) {
        oldSlideControl = instance->GetSlideControl();
    }
    instance->SetSlideControl(1.0f);
}
void Movement::FixSlideControl() {
    static GorillaLocomotion::Player* instance = GorillaLocomotion::Player::get_Instance();
    if (oldSlideControl == -1.0f) {
        oldSlideControl = instance->GetSlideControl();
    }
    instance->SetSlideControl(oldSlideControl);
}
void Movement::TFly() {
    if (XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Right) > .5f) {
        static auto inst = GorillaLocomotion::Player::get_Instance();
        static Rigidbody* rb = inst->GetPlayerRigidBody();
        inst->GetTransform()->SetPosition(inst->GetTransform()->GetPosition() + inst->GetHeadCollider()->GetTransform()->GetForward() * Time::GetDeltaTime() * flySpeed);
        rb->SetVelocity(Vector3::zero);
    }
}
void Movement::UpAndDown() {
    static auto inst = GorillaLocomotion::Player::get_Instance();
    static Rigidbody* rb = inst->GetPlayerRigidBody();

    if (XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Right) > .5f) {
        Vector3 velo = rb->GetVelocity();
        Vector3 additive = ((Vector3::up * Time::GetDeltaTime()) * 30.f);
        rb->SetVelocity( velo + additive );
    }
    if (XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Left) > .5f) {
        Vector3 velo = rb->GetVelocity();
        Vector3 additive = ((Vector3::up * Time::GetDeltaTime()) * -30.f);
        rb->SetVelocity( velo + additive );
    }
}
void Movement::CarMonkey() {
    static auto inst = GorillaLocomotion::Player::get_Instance();
    static Rigidbody* rb = inst->GetPlayerRigidBody();

    if (XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Right) > .5f) {
        Vector3 velo = rb->GetVelocity();
        Vector3 additive = ((inst->GetBodyCollider()->GetTransform()->GetForward() * Time::GetDeltaTime()) * 30.f);
        rb->SetVelocity( velo + additive );
    }
    if (XRInput::GetFloatFeature(FloatFeature::Trigger, Controller::Left) > .5f) {
        Vector3 velo = rb->GetVelocity();
        Vector3 additive = ((inst->GetBodyCollider()->GetTransform()->GetForward() * Time::GetDeltaTime()) * -30.f);
        rb->SetVelocity( velo + additive );
    }
}

void Movement::StickLongArms() {
    static auto inst = GorillaLocomotion::Player::get_Instance();
    Vector3 offset = Vector3(0, 0, 1.0f) ;
    offset.z + (armMult - 1.0f);
    inst->SetLeftHandOffset(offset);
    inst->SetRightHandOffset(offset);
}

void Movement::FixStickLongArms() {
    static auto inst = GorillaLocomotion::Player::get_Instance();
    Vector3 offset = Vector3::zero;
    inst->SetLeftHandOffset(offset);
    inst->SetRightHandOffset(offset);
}

void Movement::VeloFly() {
    static auto inst = GorillaLocomotion::Player::get_Instance();
    static auto rb = inst->GetPlayerRigidBody();

    if (XRInput::GetBoolFeature(BoolFeature::PrimaryButton, Controller::Right)) {
        rb->SetVelocity(rb->GetVelocity() + (inst->GetRightHandTransform()->GetForward() * Time::GetDeltaTime() * (flySpeed * 2)));
    }
}

void Movement::BarkFly() {
    static auto inst = GorillaLocomotion::Player::get_Instance();
    static auto rb = inst->GetPlayerRigidBody();
    Vector2 joy = XRInput::GetVector2Feature(Vector2Feature::Primary2DAxis, Controller::Left);

    if (std::abs(joy.x) > 0.3 || std::abs(joy.y) > 0.3)
    {
        Transform* ptran = inst->GetTransform();
        Transform* htran = inst->GetHeadCollider()->GetTransform();
        Vector3 vec = (htran->GetPosition() * Time::GetDeltaTime() * (joy.y * flySpeed)) + (htran->GetRight() * Time::GetDeltaTime() * (joy.x * flySpeed));
        rb->SetVelocity(Vector3::zero);
    }
}

void Movement::JoystickFly() {
    static auto inst = GorillaLocomotion::Player::get_Instance();
    static auto rb = inst->GetPlayerRigidBody();

    Vector2 leftJoystick = XRInput::GetVector2Feature(Vector2Feature::Primary2DAxis, Controller::Left);
    Vector2 rightJoystick = XRInput::GetVector2Feature(Vector2Feature::Primary2DAxis, Controller::Right);

    Vector3 inputDirection = Vector3(leftJoystick.x, rightJoystick.y, leftJoystick.y);
    Vector3 playerForward = inst->GetBodyCollider()->GetTransform()->GetForward();
    playerForward.y = 0;
    Vector3 playerRight = inst->GetBodyCollider()->GetTransform()->GetRight();
    playerRight.y = 0;

    Vector3 velocity = inputDirection.x * playerRight + rightJoystick.y * Vector3::up + inputDirection.z * playerForward;
    velocity *= inst->GetTransform()->GetLocalScale().x * flySpeed;
    rb->SetVelocity(Vector3::Lerp(rb->GetVelocity(), velocity, 0.12875f));
}