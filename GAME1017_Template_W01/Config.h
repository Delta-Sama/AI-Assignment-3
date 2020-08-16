#pragma once
#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "Engine.h"

// NODES:
const int MAX_CHECK = 2;
const int PREV_NODES_SIZE = 4;
const float DETECT_RADIUS = 100;
const float SWITCH_NODE_DISTANCE = 24;

// PHYSICS:
const float STANDART_DRAG = 0.88;

// GLOBAL MELEE:
const float MELEE_DIST = 60.0;
const float MELEE_ANGLE = 50.0;

// GLOBAL RANGE:
const float RANGE_DISTANCE = 250.0;

// GLOBAL AI SETTINGS:
const float MIN_SEEK_DISTANCE = 10;
const float MIN_MOVE_ANGLE_DISTANCE = 50.0;
const float WAIT_BEHIND_COVER_TIME = FPS * 3;
const float TUNNEL_ENTITY_WIDTH = 10;
const float AVOID_DISTANCE = MELEE_DIST * 2;
const float HIDE_COOLDOWN = FPS * 10;
const float MAX_COVER_TIME = FPS * 6;

// ENTITY:
const float MAX_ENTITY_VELOCITY = 3.0;
const float ENEMY_MELEE_TIME = FPS * 0.4;
const float ENEMY_PROJ_TIME = FPS * 0.6;
const float ENEMY_MELEE_DAMAGE = 10;
const float WAIT_AFTER_ATTACK = FPS * 0.5;
const float ENEMY_RANGE_TIME = FPS * 0.6;
const float HIT_FRAMES = 5;

#endif