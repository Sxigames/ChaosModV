/*
    Effect by ProfessorBiddle, based on code from DrUnderscore, Idea from Synfetic
*/

#include <stdafx.h>
static Camera flippedCamera = 0;
float camRot = 0.f;
const float camRotRate = 1.2f;

static void UpdateCamera()
{
    auto coord = CAM::GET_GAMEPLAY_CAM_COORD();
    auto rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
    auto fov = CAM::GET_GAMEPLAY_CAM_FOV();
    CAM::SET_CAM_PARAMS(flippedCamera, coord.x, coord.y, coord.z, rot.x, camRot, rot.z, fov, 0, 1, 1, 2);
}

static void OnStart()
{
    flippedCamera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
    CAM::RENDER_SCRIPT_CAMS(true, true, 10, 1, 1, 1);
}

static void OnTick()
{
    camRot += camRotRate;
    CAM::SET_CAM_ACTIVE(flippedCamera, true);
    UpdateCamera();
}

static void OnStop()
{
    CAM::SET_CAM_ACTIVE(flippedCamera, false);
    CAM::RENDER_SCRIPT_CAMS(false, true, 700, 1, 1, 1);
    CAM::DESTROY_CAM(flippedCamera, true);
    flippedCamera = 0;
}

static RegisterEffect registerEffect(EFFECT_PLAYER_SPIN_CAMERA, OnStart, OnStop, OnTick);
