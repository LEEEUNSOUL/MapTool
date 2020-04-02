#include "stdafx.h"
#include "Tile.h"
#include "./Manage/MapManager.h"



void Tile::Save(BinaryWriter * w, Tile * tile)
{
	w->String(tile->imgKey);
	w->String(tile->objectKey);

	w->Int((int)tile->index.x);
	w->Int((int)tile->index.y);
	w->Int(tile->attribute);
}


void Tile::Load(BinaryReader * r, Tile * tile)
{
	tile->imgKey = r->String();
	if (tile->imgKey.empty() == false)
	{
		tile->SetImg(tile->imgKey);
	}
	tile->objectKey = r->String();
	if (tile->objectKey.empty() == false)
	{
		tile->SetObjectImg(tile->objectKey);
	}

	tile->index.x = (LONG)(r->Int());
	tile->index.y = (LONG)(r->Int());
	tile->attribute = (ATTRIBUTE)r->Int();
}


Tile::Tile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:GameObject(name, pos, size)
{
	AddCallback("Tile", [&](TagMessage msg) {
		LOG->Print("Pick X : %d , Y : %d", index.x, index.y);
		string key = msg.Data->GetValue<string>();
		SetImg(key); 
	});


	AddCallback("Object", [&](TagMessage msg) {
		string key = msg.Data->GetValue<string>();
		SetObjectImg(key); 
	});
}


Tile::~Tile()
{

}


void Tile::Init()
{
	Super::Init(); 
}


void Tile::Release()
{
	Super::Release();
}


void Tile::Update()
{
	Super::Update();
}


void Tile::Render()
{
	Super::Render();

	//Basic tile render
	if (Img)
	{
		Img->Render(rc, nullptr);
	}

	//object tile render
	if (object)
	{
		D3DXVECTOR2 pos = transform.GetPos() + D3DXVECTOR2(MapManager::tileSize.x*0.5f, MapManager::tileSize.y);
		FloatRect area = FloatRect(pos, object->GetFrameSize(), Pivot::BOTTOM);
		object->Render(area, nullptr);
	}

	if (attribute == AT_WALKUNABLE)
	{
		p2DRenderer->DrawLine(D3DXVECTOR2(rc.left, rc.top), D3DXVECTOR2(rc.right, rc.bottom), nullptr, DefaultBrush::red, 1.5f);
		p2DRenderer->DrawLine(D3DXVECTOR2(rc.right, rc.top), D3DXVECTOR2(rc.left, rc.bottom), nullptr, DefaultBrush::red, 1.5f);
	}
}


void Tile::SetImg(string imgKey)
{
	Img = _ImageManager->FindTexture(imgKey);
	this->imgKey = imgKey;
}


void Tile::SetObjectImg(string imgKey)
{
	object = _ImageManager->FindTexture(imgKey);
	this->objectKey = imgKey;
}


void Tile::SetIndex(POINT pt)
{
	index = pt;
}

