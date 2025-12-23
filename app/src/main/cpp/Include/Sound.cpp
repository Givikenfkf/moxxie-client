#include <Mods.hpp>
#include "GorillaLocomotion.hpp"

VRRig vrrig;

void Sound::Init() {

}

void Sound::BreakAudio() {
    //crystal
    vrrig.PlayHandTap(43, true, 999999.f);
    //snow
    vrrig.PlayHandTap(31, true, 999999.f);
    //cloth
    vrrig.PlayHandTap(3, true, 999999.f);
    //concrete or stone
    vrrig.PlayHandTap(1, true, 999999.f);
    //wood
    vrrig.PlayHandTap(8, true, 999999.f);
    //metal
    vrrig.PlayHandTap(18, true, 999999.f);
}