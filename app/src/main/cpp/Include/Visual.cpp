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

void Visual::Init() {

}

void Visual::SeeNetworkTriggers() {
    Class GorillaJoinTrigger = Class("GorillaNetworking", "GorillaNetworkJoinTrigger");
    Array<Object*>* objs = GameObject::FindObjectsOfType(GorillaJoinTrigger.GetMonoType());
    if (!GorillaJoinTrigger) {
        GorillaJoinTrigger = Class("", "GorillaNetworkJoinTrigger");
    }

    GameObject* obj = (GameObject*)objs->GetSize();

    for (int i = 0; i < objs->GetSize(); i++) {
        GameObject* cube = nullptr;
        cube = GameObject::CreatePrimitive(PrimitiveType::Cube);
        cube->SetActive(true);
        cube->SetName("VCube");
        Shader* shader = Shader::Find("GUI/Text Shader");
        MeshRenderer* rend = reinterpret_cast<MeshRenderer*>(obj->GetComponent(MeshRenderer::GetType()));
        rend->GetGameObject()->SetActive(true);
        BNM_LOG_INFO("attempting to enable mesh rends");
        reinterpret_cast<Renderer*>(cube->GetComponent(Renderer::GetType()))->GetMaterial()->SetShader(shader);
        reinterpret_cast<Renderer*>(cube->GetComponent(Renderer::GetType()))->GetMaterial()->SetColor(Color::magenta);
    }
}