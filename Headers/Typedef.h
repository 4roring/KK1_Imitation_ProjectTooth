#pragma once

class CGameObject;

typedef std::list<CGameObject*> OBJLIST;
typedef D3DXVECTOR3 Vector3;

typedef std::unordered_map<std::wstring, class CTexture*> TEXTUREMAP;
typedef std::unordered_map<std::wstring, TEXINFO*> SINGLETEXMAP;
typedef std::unordered_map<std::wstring, std::vector<TEXINFO*>> MULTITEXMAP;
typedef std::unordered_map<std::wstring, LPRECT> ATLASTEXMAP;
typedef std::unordered_map<std::wstring, struct FMOD_SOUND*> SOUNDMAP;

typedef std::vector<COLLTILE*> VECCOLLTILE;
typedef std::vector<CGameObject*> VECRENDER;

typedef std::list<ASTARNODE*> ASTARNODELIST;

// ÅøÀü¿ë
typedef std::list<TEXPATH*> TEXPATHLIST;
typedef std::vector<DECO*> VECDECO;

