#include "stdafx.h"
#include "SampleTile.h"
#include "./Object/Tile.h"
#include "./Manage/MapManager.h"


SampleTile::SampleTile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	_tileNum = 0;
}


SampleTile::~SampleTile()
{
}


void SampleTile::Init()
{
	Super::Init();
	CreateSampleTile();
	
	WCHAR Terrain[128] = L"../_Resources/Map/Terrain";
	Path::FileSearch(Terrain, [&](wstring file) {
		wstring fileW = file;
		string fileM = String::WStringToString(fileW);
		String::Replace(&fileM, "\\", "/");
		string key = Path::GetFileNameWithoutExtension(fileM);

		_terrain.push_back(key);
	});

	WCHAR KitchenFloor[128] = L"../_Resources/Map/KitchenFloor";
	Path::FileSearch(KitchenFloor, [&](wstring file) {
		wstring fileW = file;
		string fileM = String::WStringToString(fileW);
		String::Replace(&fileM, "\\", "/");
		string key = Path::GetFileNameWithoutExtension(fileM);
		_kitchenFloor.push_back(key);
	});
}


void SampleTile::Release()
{
	Super::Release();
}


void SampleTile::Update()
{
	Super::Update();

	if (map->GetControltileNum() == 0 || 
		map->GetControltileNum() == 1)
		ClickTile(); 
}


void SampleTile::Render()
{
	Super::Render();
	
	for (int i = 0; i < (int)vSampleTile.size(); i++)
	{
		vSampleTile[i]->Render();
	}

	for (int i = 0; i < vSampleTile.size(); i++)
	{
		vSampleTile[i]->SetImg("");
		if (map->GetControltileNum() == 0)  //외부 지형 및 바닥 
		{
			SetTile(_terrain);
		}
		else if (map->GetControltileNum() == 1) //주방 바닥 및 벽 
		{
			for (int i = 0; i < vSampleTile.size(); i++)
			{
				vSampleTile[i]->SetImg("");
			}
			SetTile(_kitchenFloor);
		}
	}
}


void SampleTile::ClickTile()
{

	if (Mouse::Get()->Down(0))
	{
		if ((int)vSampleTile.size() != 0)
		{
			D3DXVECTOR2 mouse;
			memcpy(&mouse, &Mouse::Get()->GetPosition(), sizeof(float) * 2);

			for (int i = 0;i < (int)vSampleTile.size();i++)
			{
				if (Math::IsPointInAABB(vSampleTile[i]->GetCollider(), mouse))
				{
					currentTile = vSampleTile[i]->GetImgKey();
					break;
				}
			}
		}
	}


	else if (Mouse::Get()->Down(VK_ESCAPE))
	{
		currentTile = "None";
	}
}


void SampleTile::SetTile(vector<string> Tiletype)
{
	for (int i = 0; i < Tiletype.size(); i++)
		vSampleTile[i]->SetImg(Tiletype[i]);
}


void SampleTile::CreateSampleTile()
{
	D3DXVECTOR2 start = { WinSizeX - 250, 50 };
	D3DXVECTOR2 offset = { 10,10 };
	
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			D3DXVECTOR2 pos = start + D3DXVECTOR2(50 * x , 50 * y);

			Tile* tile = new Tile("SampleTile", pos, { 50, 50 });
			vSampleTile.push_back(tile);
		}
	}

}


