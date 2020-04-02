#pragma once

class MapManager; 

class ControlUI 
{
	
private:
	FloatRect _noneBtn; 
	FloatRect _saveBtn; 
	FloatRect _loadBtn;
	FloatRect _eraseBtn; 
	FloatRect _walkUnableBtn;
	FloatRect _preTile; 
	FloatRect _nextTile;

	MapManager* mapManager; 
	
public:
	ControlUI();

	~ControlUI();

	//�ʱ�ȭ
	void Init();
	//�޸� ����
	void Release();
	//���� ��ƾ
	void Update();

	void Render();

	void SetLinkWithMap(MapManager* mapManager) { this->mapManager = mapManager; }
};

