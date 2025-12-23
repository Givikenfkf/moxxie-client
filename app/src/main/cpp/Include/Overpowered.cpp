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
#include "BNMResolve.hpp"
#include <limits>
#include "PhotonResolve.hpp"

void Overpowered::Init() {

}
static bool nameChanged = false;

void Overpowered::TextWall() {
    if (XRInput::GetBoolFeature(BoolFeature::TriggerButton, Controller::Right)) {
        if (!nameChanged) {
            static Class PhotonNetwork = Class(O("Photon.Pun"), O("PhotonNetwork"));
            static Property<void *> LocalPlayer = PhotonNetwork.GetProperty(O("LocalPlayer"));
            static Class Player = Class(O("Photon.Realtime"), O("Player"));
            static Property<Mono::String *> NickName = Player.GetProperty(O("NickName"));

            static Class PlayerPrefs = Class(O("UnityEngine"), O("PlayerPrefs"));
            static Method<void *> SetString = PlayerPrefs.GetMethod(O("SetString"), 2);

            static Class GorillaComputer = Class(O("GorillaNetworking"), O("GorillaComputer"));
            static Field<Il2CppObject *> instance = GorillaComputer.GetField(O("instance"));
            static Field<Mono::String *> savedName = GorillaComputer.GetField(O("savedName"));

            std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

            std::string newName = "<size=30000><color=magenta>{\n{</color></size>";

            Mono::String *monoName = CreateMonoString(newName);
            NickName[LocalPlayer()] = monoName;
            auto inst = instance.Get();
            SetString(CreateMonoString(O("playerName")), monoName);
            savedName[inst] = monoName;
            nameChanged = true;
        }
        PhotonNetwork::Instantiate("Network Player", Vector3::zero, Quaternion::identity);
    }
}