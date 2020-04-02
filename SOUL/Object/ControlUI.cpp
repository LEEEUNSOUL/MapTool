#include "stdafx.h"
#include "ControlUI.h"
#include "./Object/Tile.h"
#include "./Manage/MapManager.h"
#include "./Object/SampleTile.h"


ControlUI::ControlUI()
{

}

ControlUI::~ControlUI()
{

}

void ControlUI::Init()
{
	//맵툴 버튼 
	_noneBtn = FloatRect(D3DXVECTOR2(1387, 521),
						 D3DXVECTOR2(135, 39), Pivot::LEFT_TOP); //아무것도 선택하지 않은 선택 

	_eraseBtn = FloatRect(D3DXVECTOR2(1389, 573),
						  D3DXVECTOR2(136, 35), Pivot::LEFT_TOP); //타일 지우개 버튼 

	_walkUnableBtn = FloatRect(D3DXVECTOR2(1339,627),
							  D3DXVECTOR2(228, 34), Pivot::LEFT_TOP); //걸을 수 없는 지역 설정

	_saveBtn = FloatRect(D3DXVECTOR2(1385, 735),
					     D3DXVECTOR2(132, 33), Pivot::LEFT_TOP); //저장 버튼

	_loadBtn = FloatRect(D3DXVECTOR2(1385, 797),
						 D3DXVECTOR2(138, 36), Pivot::LEFT_TOP); //로드 버튼

	_preTile = FloatRect(D3DXVECTOR2(1320, 410),
						 D3DXVECTOR2(70, 36), Pivot::LEFT_TOP); //이전 타일 선택

	_nextTile = FloatRect(D3DXVECTOR2(1510, 410),
						 D3DXVECTOR2(70, 36), Pivot::LEFT_TOP); //다음 타일 선택
}


void ControlUI::Release()
{
}


void ControlUI::Update()
{
	//마우스 클릭 시 렉트와 충돌 검사 

	if (Mouse::Get()->Down(0))
	{
		D3DXVECTOR2 mouse;

		memcpy(&mouse, &Mouse::Get()->GetPosition(), sizeof(float) * 2);

		if (Math::IsPointInAABB(_noneBtn, mouse))
		{
			mapManager->SetBrushType(BRUSHTYPE_NONE);
		}

		else if (Math::IsPointInAABB(_eraseBtn, mouse))
		{
			mapManager->SetBrushType(ERASE);
		}

		else if (Math::IsPointInAABB(_walkUnableBtn, mouse))
		{
			mapManager->SetBrushType(WALKUNABLE);
		}

		else if (Math::IsPointInAABB(_saveBtn, mouse))
		{
			D3DDesc desc;
			pRenderer->GetDesc(&desc);
			Path::SaveFileDialog(L"", Path::TerrainFilter, ResourcePath + L"Terrain/", [&](wstring file) {
				mapManager->Save(file);
			}, desc.Handle);
		}

		else if (Math::IsPointInAABB(_loadBtn, mouse))
		{
			D3DDesc desc;
			pRenderer->GetDesc(&desc);
			Path::OpenFileDialog(L"", Path::TerrainFilter, ResourcePath + L"Terrain/", [&](wstring file) {
				mapManager->Load(file);
			}, desc.Handle);

		}

		else if (Math::IsPointInAABB(_preTile, mouse))
		{
			mapManager->ControlTileNum(-1);
		}

		else if (Math::IsPointInAABB(_nextTile, mouse))
		{
			mapManager->ControlTileNum(1);
		}
	}
}


void ControlUI::Render()
{
	if (SceneBase::DebugMode)
	{
		p2DRenderer->DrawRectangle(_preTile, nullptr, DefaultBrush::red, 0.9);
		p2DRenderer->DrawRectangle(_nextTile, nullptr, DefaultBrush::red, 0.9);
		p2DRenderer->DrawRectangle(_noneBtn, nullptr, DefaultBrush::red, 0.9);
		p2DRenderer->DrawRectangle(_eraseBtn, nullptr, DefaultBrush::red, 0.9);
		p2DRenderer->DrawRectangle(_walkUnableBtn, nullptr, DefaultBrush::red, 0.9);
		p2DRenderer->DrawRectangle(_saveBtn, nullptr, DefaultBrush::red, 0.9);
		p2DRenderer->DrawRectangle(_loadBtn, nullptr, DefaultBrush::red, 0.9);
	}
}
 
