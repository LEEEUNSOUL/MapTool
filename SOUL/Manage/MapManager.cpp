#include "stdafx.h"
#include "MapManager.h"

#include "./Object/Tile.h"
#include "./Object/SampleTile.h"
#include "./Object/ObjectTile.h"

#include "./Object/ControlUI.h"


D3DXVECTOR2 MapManager::tileSize = { 50, 50 };
POINT MapManager::maxTileNum = { 60, 60 };


MapManager::MapManager()
{
	_brushType = BRUSHTYPE_NONE;
}


MapManager::~MapManager()
{
	Release();
	SafeDelete(sampleTile); 
}


void MapManager::Init()
{
	_controltileNum = 0; 
	
	//Make Tile 
	for (int i = 0; i < maxTileNum.y; i++)
	{
		for (int j = 0; j < maxTileNum.x; j++)
		{
			Tile* tile = new Tile("Tile", D3DXVECTOR2(j*tileSize.x, i*tileSize.y), MapManager::tileSize);
			tile->SetIndex({ j,i });
			vTile.push_back(tile);
		}
	}

	//Make Tile 
	for (int i = 0; i < maxTileNum.y; i++)
	{
		for (int j = 0; j < maxTileNum.x; j++)
		{
			Tile* objtile = new Tile("ObjectTile", D3DXVECTOR2(j*tileSize.x, i*tileSize.y), MapManager::tileSize);
			objtile->SetIndex({ j,i });
			vObjectTile.push_back(objtile);
		}
	}

	//Find Image by 'Image Key'
	background = _ImageManager->FindTexture("background");  
	toolPanel = _ImageManager->FindTexture("mapToolBackGround");

	sampleTile = new SampleTile("", D3DXVECTOR2(), D3DXVECTOR2());
	sampleTile->Init();
	sampleTile->SetLinkWithMapManager(this);

	objectTile = new ObjectTile("", D3DXVECTOR2(), D3DXVECTOR2());
	objectTile->Init();
	objectTile->SetLinkWithMapManager(this); 

	controlUI = new ControlUI(); 
	controlUI->Init();
	controlUI->SetLinkWithMap(this); 

	isDraw = false;
}


void MapManager::Release()
{
	for (Tile* tile : vTile)
		SafeDelete(tile);
	vTile.clear();
	vObjectTile.clear(); 
}


void MapManager::Update()
{
	sampleTile->Update();
	objectTile->Update();
	controlUI->Update();

	SetBrush();
	KeyControl();

	for (int i = 0;i < (int)vTile.size();i++)
		vTile[i]->Update();

	for (int i = 0;i < (int)vObjectTile.size();i++)
		vObjectTile[i]->Update();
}


void MapManager::Render()
{
	FloatRect backgroundRc = FloatRect(D3DXVECTOR2(0, 0), D3DXVECTOR2(2640, 1940), Pivot::LEFT_TOP);
	background->Render(backgroundRc, nullptr);

	for (int i = 0;i < (int)vTile.size();i++)
		vTile[i]->Render();

	for (int i = 0;i < (int)vObjectTile.size();i++)
		vObjectTile[i]->Render();

	if (isDraw)
	{
		FloatRect drawTile = FloatRect(_startDrawPos,
									   D3DXVECTOR2(_endDrawPos.x - _startDrawPos.x + MapManager::tileSize.x, 
										           _endDrawPos.y - _startDrawPos.y + MapManager::tileSize.y), 
												   Pivot::LEFT_TOP);
		p2DRenderer->DrawRectangle(drawTile, nullptr, DefaultBrush::red, 0.9);
	}
}


void MapManager::UiRender()
{
	_toolPanelRc = FloatRect(D3DXVECTOR2(WinSizeX - 300, 0), 
							 D3DXVECTOR2(304, 900), 
							 Pivot::LEFT_TOP);

	toolPanel->Render(_toolPanelRc, nullptr);

	sampleTile->Render();
	objectTile->Render();
	controlUI->Render(); 
}


void MapManager::KeyControl()
{
	Tile* tile = GetTIleAsPos(CAMERA->GetMousePos());


	if (Mouse::Get()->GetPosition().x < _toolPanelRc.left
		&& tile != nullptr && _brushType != WALKUNABLE
		&& _brushType != ERASE)
	{
		if (Mouse::Get()->Down(0))
		{
			isDraw = true;
			startIndex = tile->GetIndex();
			_startDrawPos = IndexToPos(startIndex.x, startIndex.y);
		}

		if (Mouse::Get()->Press(0))
		{
			endIndex = tile->GetIndex();
			_endDrawPos = IndexToPos(endIndex.x, endIndex.y);
		}

		else if (Mouse::Get()->Up(0))
		{
			endIndex = tile->GetIndex();
			_endDrawPos = IndexToPos(endIndex.x, endIndex.y);
			ReverseNum(startIndex, endIndex);
			isDraw = false;

			string currrentTile = sampleTile->GetCurrentTile();

			if (currrentTile != "None" || currrentTile.empty())
			{
				for (int y = startIndex.y; y <= endIndex.y; y++)
				{
					for (int x = startIndex.x; x <= endIndex.x; x++)
					{
						if (_controltileNum == 0 || _controltileNum == 1)
						{
							string currrentTile1 = sampleTile->GetCurrentTile();
							CreateImg({ x, y }, "Tile", currrentTile1);
						}

						if (_controltileNum == 2 || _controltileNum == 3)
						{
							CreateObjectImg({ x, y }, "Object", objectTile->GetCurrentTile());
						}
					}
				}
			}
		}
	}
}


void MapManager::CreateImg(POINT index, string messageName, string currentTile)
{
	Tile* tile = GetTileAsIndex(index);

	if (tile == nullptr) return; 

	_MessagePool->ReserveMessage(tile, messageName, 0.f, currentTile);
}


void MapManager::CreateObjectImg(POINT index, string messageName, string currentTile)
{
	Tile* tile = GetObjectTileAsIndex(index);

	if (tile == nullptr) return;

	_MessagePool->ReserveMessage(tile, messageName, 0.f, currentTile);
}


void MapManager::SetBrush()
{
	Tile* tile = GetTIleAsPos(CAMERA->GetMousePos());
	Tile* objtile = GetObjectAsPos(CAMERA->GetMousePos());

	if (_brushType == WALKUNABLE && Mouse::Get()->Down(0))
	{
		tile->SetAttribute(AT_WALKUNABLE);
	}
	//Erase & Mouse LeftButton == Erase Img 
	else if (_brushType == ERASE && Mouse::Get()->Down(0))
	{
		tile->SetImg(""); 
		objtile->SetObjectImg("");
	}
	//Erase & Mouse RightButton == Erase Attribute
	else if (_brushType == ERASE && Mouse::Get()->Down(1)) 
	{
		tile->SetAttribute(NONE);
	}
}


void MapManager::Save(wstring file)
{
	//시작하자마자 타일 찍는 것 방지
	sampleTile->Reset();
	objectTile->Reset();

	wstring path = file;

	if (String::Contain(path, L".terrain") == false)
		path.append(L".terrain");

	BinaryWriter* w = new BinaryWriter();
	w->Open(file);
	{
		w->Int((int)vTile.size());
		for (int i = 0; i < vTile.size(); i++)
		{
			Tile::Save(w, vTile[i]);
		}

		w->Int((int)vObjectTile.size());
		for (int i = 0; i < vObjectTile.size(); i++)
		{
			Tile::Save(w, vObjectTile[i]);
		}
	}
	w->Close();
}


void MapManager::Load(wstring file)
{
	sampleTile->Reset();
	objectTile->Reset();

	if (vTile.empty() == false)
	{
		for (Tile* tile : vTile)
			SafeDelete(tile);
		vTile.clear();
	}
	if (vObjectTile.empty() == false)
	{
		for (Tile* tile : vObjectTile)
			SafeDelete(tile);
		vObjectTile.clear();
	}

	startIndex = { 0,0 };
	BinaryReader* r = new BinaryReader();
	
	r->Open(file);
	{
		for (int i = 0; i < maxTileNum.y; i++)
		{
			for (int j = 0; j < maxTileNum.x; j++)
			{
				Tile* tile = new Tile("Tile", D3DXVECTOR2(j*tileSize.x, i*tileSize.y), MapManager::tileSize);
				tile->SetIndex({ j,i });
				vTile.push_back(tile);
			}
		}

		for (int i = 0; i < maxTileNum.y; i++)
		{
			for (int j = 0; j < maxTileNum.x; j++)
			{
				Tile* tile = new Tile("Object", D3DXVECTOR2(j*tileSize.x, i*tileSize.y), MapManager::tileSize);
				tile->SetIndex({ j,i });
				vObjectTile.push_back(tile);
			}
		}

		int count = r->Int();
		for (int i = 0;i < count; i++)
		{
			Tile::Load(r, vTile[i]);
		}
		
		int count1 = r->Int();
		for (int i = 0;i < count1; i++)
		{
			Tile::Load(r, vObjectTile[i]);
		}
	}

	r->Close();
}


void MapManager::ReverseNum(POINT startpos, POINT endpos)
{
	float temp1;
	if (startpos.x > endpos.x)
	{
		temp1 = startpos.x;
		startpos.x = endpos.x;
		endpos.x = temp1;
	}
	if (startpos.y > endpos.y)
	{
		temp1 = startpos.y;
		startpos.y = endpos.y;
		endpos.y = temp1;
	}
}


void MapManager::ControlTileNum(int num)
{
	_controltileNum += num;

	if (objectTile->GetvObjectTile().size() == NULL ||
		sampleTile->GetvSampleTile().size() == NULL) return;

	if (_controltileNum == 0 || _controltileNum == 1)
	{
		for (int i = 0; i < sampleTile->GetvSampleTile().size(); i++)
		{
			sampleTile->GetvSampleTile()[i]->SetImg("");
		}
	}
	if (_controltileNum == 2 || _controltileNum == 3)
	{
		for (int i = 0; i < objectTile->GetvObjectTile().size(); i++)
		{
			objectTile->GetvObjectTile()[i]->SetObjectImg("");
		}
	}
}

///////////////////////////////////////////////////////////
//////////////// Calcultate Tile Index ////////////////////
//////////////////////////////////////////////////////////

Tile * MapManager::GetTileAsIndex(POINT index)
{
	//2차배열을 1차 배열로 가져와야 한다. 
	if (index.x <0 || index.y< 0 || index.x > MapManager::maxTileNum.x - 1 || index.y > MapManager::maxTileNum.y)
	{
		return nullptr;
	}

	return vTile[index.y * MapManager::maxTileNum.x + index.x];
}


Tile * MapManager::GetObjectTileAsIndex(POINT index)
{
	//2차배열을 1차 배열로 가져와야 한다. 
	if (index.x <0 || index.y< 0 || index.x > MapManager::maxTileNum.x - 1 || index.y > MapManager::maxTileNum.y)
	{
		return nullptr;
	}

	return vObjectTile[index.y * MapManager::maxTileNum.x + index.x];
}


Tile * MapManager::GetTIleAsPos(D3DXVECTOR2 pos)
{
	POINT pt = MapManager::PosToIndex(pos);

	return GetTileAsIndex(pt);
}


Tile * MapManager::GetObjectAsPos(D3DXVECTOR2 pos)
{
	POINT pt = MapManager::PosToIndex(pos);

	return GetObjectTileAsIndex(pt);
}


D3DXVECTOR2 MapManager::IndexToPos(int x, int y)
{
	return D3DXVECTOR2(x*tileSize.x, y*tileSize.y);
}


POINT MapManager::PosToIndex(D3DXVECTOR2 pos)
{
	POINT pt = { -1, -1 };

	if (pos.x >= 0 && pos.y >= 0) //화면 안에 있는 것만 인덱스 반환하기 
	{
		pt.x = (int)(pos.x / tileSize.x);
		pt.y = (int)(pos.y / tileSize.y);
	}

	return pt;
}



