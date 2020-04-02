#include "stdafx.h"
#include "ObjectTile.h"
#include "./Object/Tile.h"
#include "./Manage/MapManager.h"


ObjectTile::ObjectTile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	_tileNum = 0;
}


ObjectTile::~ObjectTile()
{
}

void ObjectTile::Init()
{
	Super::Init();
	CreateObjectTile(); 


	WCHAR KitchenWall[128] = L"../_Resources/Map/KitchenWall";
	Path::FileSearch(KitchenWall, [&](wstring file) {
		wstring fileW = file;
		string fileM = String::WStringToString(fileW);
		String::Replace(&fileM, "\\", "/");
		string key = Path::GetFileNameWithoutExtension(fileM);
		_kitchenWall.push_back(key);
	});


	WCHAR InteriorTile[128] = L"../_Resources/Map/InteriorTile";
	Path::FileSearch(InteriorTile, [&](wstring file) {
		wstring fileW = file;
		string fileM = String::WStringToString(fileW);
		String::Replace(&fileM, "\\", "/");
		string key = Path::GetFileNameWithoutExtension(fileM);
		_interiorTile.push_back(key);
	});
}

void ObjectTile::Release()
{
	Super::Release();
}

void ObjectTile::Update()
{
	Super::Update();
	if (map->GetControltileNum() == 2 || 
		map->GetControltileNum() == 3)
		ClickTile();
}

void ObjectTile::Render()
{
	Super::Render();

	for (int i = 0; i < (int)vObjectTile.size(); i++)
	{
		vObjectTile[i]->Render();
	}
	for (int i = 0; i < vObjectTile.size(); i++)
	{
		vObjectTile[i]->SetImg("");
		if (map->GetControltileNum() == 2)
		{
			SetTile(_kitchenWall);
		}
		else if (map->GetControltileNum() == 3)
		{
			for (int i = 0; i < vObjectTile.size(); i++)
			{
				vObjectTile[i]->SetImg("");
			}
			SetTile(_interiorTile);
		}
	}
}

void ObjectTile::ClickTile()
{
	//클릭했을 때 ImageKey값 추출 
	if (Mouse::Get()->Down(0))
	{
		if ((int)vObjectTile.size() != 0)
		{
			D3DXVECTOR2 mouse;
			memcpy(&mouse, &Mouse::Get()->GetPosition(), sizeof(float) * 2);

			for (int i = 0;i < (int)vObjectTile.size();i++)
			{
				if (Math::IsPointInAABB(vObjectTile[i]->GetCollider(), mouse))
				{
					//마우스로 클릭한 ImageKey값 currentTile에 저장
					currentTile = vObjectTile[i]->GetImgKey();
					break;
				}
			}
		}
	}

	else if (Mouse::Get()->Down(VK_ESCAPE))
	{
		//ESC 버튼 누르면 타일 선택 안한 것 
		currentTile = "None";
	}
}


void ObjectTile::SetTile(vector<string> Tiletype)
{
	for (int i = 0; i < Tiletype.size(); i++)
		vObjectTile[i]->SetImg(Tiletype[i]);
}


void ObjectTile::CreateObjectTile()
{
	D3DXVECTOR2 start = { WinSizeX - 250, 50 };
	D3DXVECTOR2 offset = { 10,10 };

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			D3DXVECTOR2 pos = start + D3DXVECTOR2(50 * x, 50 * y);

			Tile* tile = new Tile("ObjectTile", pos, {50, 50});
			vObjectTile.push_back(tile);
		}
	}
}

