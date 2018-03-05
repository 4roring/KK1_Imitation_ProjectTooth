#pragma once

class CGameObject;

typedef std::list<CGameObject*> OBJLIST;
typedef D3DXVECTOR3 Vector3;

typedef std::map<std::wstring, class CTexture*> TEXTUREMAP;
typedef std::map<std::wstring, TEXINFO*> SINGLETEXMAP;
typedef std::map<std::wstring, std::vector<TEXINFO*>> MULTITEXMAP;

typedef std::vector<ISOTILE*> VECISOTILE;
