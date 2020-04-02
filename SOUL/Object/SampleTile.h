#pragma once

class ControlUI;
class MapManager;

class SampleTile : public GameObject
{
	ClassInherited(GameObject)

private: 
	int _tileNum; 
	
	MapManager* map;

	vector<string> _terrain;
	vector<string> _kitchenFloor;
	vector<class Tile*> vSampleTile;

	string currentTile;

private:
	void SetTile(vector<string> Tiletype);
	void CreateSampleTile();
	void ClickTile();

public:
	SampleTile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	virtual~SampleTile();

	virtual void Init();

	virtual void Release();

	virtual void Update();

	virtual void Render();

	void Reset() { currentTile = "None"; } 
	void SetLinkWithMapManager(MapManager* map) { this->map = map; }
	
	string GetCurrentTile() { return currentTile; }
	vector<class Tile*> GetvSampleTile() { return vSampleTile; }

};

