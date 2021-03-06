#pragma once

enum OBJID 
{
	OBJ_LEVEL, OBJ_BACK, OBJ_HQ, OBJ_FARM, OBJ_UNITFACTORY
	, OBJ_PLAYER, OBJ_AI, OBJ_UNIT, OBJ_EFFECT
	, OBJ_DECO, OBJ_UI, OBJ_END 
};
enum OBJSTATE { STATE_PLAY, STATE_DESTROY };
enum OBJLAYER { LAYER_BACK, LAYER_OBJ, LAYER_EFFECT, LAYER_WORLDUI, LAYER_UI, LAYER_END };

enum TEXTYPE { TEX_SINGLE, TEX_MULTI, TEX_ATLAS };

enum TEAMID { TEAM_RED, TEAM_BLUE, TEAM_GREEN, TEAM_YELLO, TEAM_NEUTRAL, TEAM_END };

enum SCENEID { SCENE_LOGO, SCENE_TITLE, SCENE_STAGE, SCENE_ENDING };

enum COMMANDID { COMMAND_PLAYER, COMMAND_AI };

enum NEIGHBORTILE 
{ 
	NEIGHBOR_LEFTDOWN, NEIGHBOR_LEFT, NEIGHBOR_LEFTUP, NEIGHBOR_UP
	, NEIGHBOR_RIGHTUP, NEIGHBOR_RIGHT,  NEIGHBOR_RIGHTDOWN, NEIGHBOR_DOWN
	, NEIGHBOR_END
};

enum UNITID 
{
	UNIT_SQUIRREL, UNIT_LIZARD, UNIT_TOAD, UNIT_PIGEON, UNIT_MOLE
	, UNIT_FERRET, UNIT_CHAMELEON, UNIT_FALCON, UNIT_SKUNK, UNIT_SNAKE
	, UNIT_BADGER, UNIT_BOAR, UNIT_FOX, UNIT_OWL, UNIT_WOLF
	, UNIT_BARBEDWIRE, UNIT_LANDMINE, UNIT_BALLON, UNIT_TURRET, UNIT_ARTILLERY
	, UNIT_ALL
};

enum BULLETID
{
	 BULLET_ARTILLERY, BULLET_GRENADE, BULLET_MEDKIT, BULLET_PISTOL
	 , BULLET_SNIPER, BULLET_VENOM, BULLET_SPEAR, BULLET_MINIGUN, BULLET_END
};

enum PARTICLEID
{
	PARTICLE_BURST, PARTICLE_EXPLOSION
	, PARTICLE_END
};