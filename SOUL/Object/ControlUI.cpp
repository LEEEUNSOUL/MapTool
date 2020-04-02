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
	//���� ��ư 
	_noneBtn = FloatRect(D3DXVECTOR2(1387, 521),
						 D3DXVECTOR2(135, 39), Pivot::LEFT_TOP); //�ƹ��͵� �������� ���� ���� 

	_eraseBtn = FloatRect(D3DXVECTOR2(1389, 573),
						  D3DXVECTOR2(136, 35), Pivot::LEFT_TOP); //Ÿ�� ���찳 ��ư 

	_walkUnableBtn = FloatRect(D3DXVECTOR2(1339,627),
							  D3DXVECTOR2(228, 34), Pivot::LEFT_TOP); //���� �� ���� ���� ����

	_saveBtn = FloatRect(D3DXVECTOR2(1385, 735),
					     D3DXVECTOR2(132, 33), Pivot::LEFT_TOP); //���� ��ư

	_loadBtn = FloatRect(D3DXVECTOR2(1385, 797),
						 D3DXVECTOR2(138, 36), Pivot::LEFT_TOP); //�ε� ��ư

	_preTile = FloatRect(D3DXVECTOR2(1320, 410),
						 D3DXVECTOR2(70, 36), Pivot::LEFT_TOP); //���� Ÿ�� ����

	_nextTile = FloatRect(D3DXVECTOR2(1510, 410),
						 D3DXVECTOR2(70, 36), Pivot::LEFT_TOP); //���� Ÿ�� ����
}


void ControlUI::Release()
{
}


void ControlUI::Update()
{
	//���콺 Ŭ�� �� ��Ʈ�� �浹 �˻� 

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
 
