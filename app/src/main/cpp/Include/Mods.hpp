#pragma once
#include <vector>
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNMResolve.hpp" // bnm resolve contains all the major includes. latest: https://github.com/livku2/bnmresolve
#include <httplib.h>
#include <json.hpp>
#include <XRInput.hpp>
#include <GorillaLocomotion.hpp>
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNM/Method.hpp"
#include "BNM/MethodBase.hpp"
#include "BNM/Field.hpp"
#include "BNM/FieldBase.hpp"
#include "BNM/UnityStructures/Color.hpp"
#include "BNM/UnityStructures/Quaternion.hpp"
#include "BNM/UnityStructures/RaycastHit.hpp"
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

using namespace std;


class Settings {
private:
    void Init();
public:
    Settings() {
        Init();
    }

    int dynamicPixelsPerUnit = 1000;
    bool legacyInput = false;

    int themeIndex = 0;
    string menuColor = "magenta";
    Color menuColorColor = Color::magenta;

    bool addOutline = false;

    int predIndex = 0;

    vector<float> predAmnts
    {
        0.00625f,
        0.0125f,
        0.025f,
        0.05f
    };
    vector<string> predAmntNames
    {
        "Low",
        "Normal",
        "High",
        "Extreme"
    };

    int pullIndex = 0;
    vector<float> powers
    {
        0.05f,
        0.1f,
        0.2f,
        0.4f
    };
    vector<string> powerNames
    {
        "Normal",
        "Medium",
        "Strong",
        "Powerful"
    };


    void GotoHome();
    void GotoMovement();
    void GotoOverpowered();
    void GotoSettings();
    void GotoVisual();
    void GotoFun();
    void GotoSound();
    void GotoRig();
    void GotoComputer();
    void EnableLegacyInput();
    void DisableLegacyInput();
    void OpenDiscord();
    void ChangeArmMult();
    void HighQualityText();
    void LowQualityText();
    void AddOutline();
    void RemoveOutline();
    Color FromColor32(int r, int b, int g, int a);
    void ChangeTheme();
    void ChangePredAmount();
    void ChangePullAmount();
};

class Movement {
private:
    void Init();

public:
    Movement() {
        Init();
    }

    int armIndex = 0;
    float armMult = 1.2f;
    float predCount = 0.0125f;
    float pullPower = 0.05f;

    vector<Vector3> lastRight = vector<Vector3> { Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero };
    vector<Vector3> lastLeft = vector<Vector3> { Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero, Vector3::zero };

    void Platforms();
    void NoClip();
    void ExcelFly();
    void PSA();
    void LongArms();
    void FixLongArms();
    static void PunchMod();
    void NoTagFreeze();
    void ForceTagFreeze();
    void TeleportGun();
    void Frozone();
    static void PullMod();
    void VelocityLongArms();
    void CarMonkey();
    static void TFly();
    void UpAndDown();
    static void SlideControl();
    void FixSlideControl();
    void StickLongArms();
    void FixStickLongArms();
    void VeloFly();
    void BarkFly();
    static void JoystickFly();
};

class Visual{
private:
    void Init();

public:
    Visual() {
        Init();
    }

    Material* standardMat = nullptr;

    void Tracers();
    void Chams();
    void Beacons();
    void NameTags();
    void SeeNetworkTriggers();
};

class Sound{
private:
    void Init();

public:
    Sound() {
        Init();
    }

    void PlaySound(int idx, bool leftHand);

    void MetalSoundSpam();
    void WoodSoundSpam();
    void StoneSoundSpam();
    void ClothSoundSpam();
    void SnowSoundSpam();
    void CrystalSoundSpam();
    void SpamAll();
    void BreakAudio();
};

class Fun{
private:
    void Init();
public:
    Fun() {
        Init();
    }

    int oldBit = -1;
    int oldSamp = -1;
    bool spiderModEnabled = false;
    float overrideSlipValue = -1.0f;

    void RideGun();
    void SpiderMod();
    void DisableSpiderMod();
    void FixGrip();
    void GripMonkey();
    void SlipperyWorld();
    Object* GetMic();
    void RestartMic();
    void SetMicQuality(int bit, int samp);
    void LoudMic();
    void HighQualityMic();
    void LowQualityMic();
    void FixMic();
};

class Overpowered{
private:
    void Init();
public:
    Overpowered() {
        Init();
    }

    bool CheckMaster();
    void RPCProtection();

    void SetMaster();
    void DestroyOthers();
    void NoTagOnJoin();
    void CrashAll();
    void CrashGun();
    void TagEndSpam();
    void BanGun();
    void MatAll();
    void VibrateControllerGun();
    void VibrateAll();
    void SlowPlayerGun();
    void CosmetX();
    void TagSelf();
    void UnTagSelf();
    void TextWall();
    void SpamAllSeeds();
};

class Rig{
private:
    void Init();
public:
    Rig() {
        Init();
    }

    Vector3 emptyVector3 = Vector3(-1, -1, -1);
    Vector3 ogHeadRotOffset = Vector3(-1, -1, -1);
    Vector3 ogLhRotOffset = Vector3(-1, -1, -1);
    Vector3 ogRhRotOffset = Vector3(-1, -1, -1);

    void GhostMonkey();
    void InvisMonkey();
    void RigGun();
    void FishWalk();
    void FixRig();
    void Spaz();
    void UpsideDownHead();
    void BackwardsHead();
    void HeadSpinX();
    void HeadSpinY();
    void HeadSpinZ();
    void GrabRig();
};

class Computer{
private:
    void Init();
public:
    Computer() {
        Init();
    }

    void Disconnect();
    void JoinRandomForest();
    void JoinRandomCity();
    void JoinRandomMountains();
    void JoinRandomCaves();
    void JoinRandomCanyons();
    void RandomName();
    void JoinSPM();
    void SPMDiscord();
};