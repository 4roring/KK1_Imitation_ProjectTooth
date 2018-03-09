// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <d3dx9.h>
#include <d3d9.h>


#include <assert.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Include.h"
#include "AbsFactory.h"


// Managers
#include "GameManager.h"
#include "KeyManager.h"
#include "Device.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ViewManager.h"