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

	//초기화
	void Init();
	//메모리 해제
	void Release();
	//메인 루틴
	void Update();

	void Render();

	void SetLinkWithMap(MapManager* mapManager) { this->mapManager = mapManager; }
};

