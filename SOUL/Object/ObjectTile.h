#pragma once

class MapManager; 

class ObjectTile : public GameObject
{
	ClassInherited(GameObject)

private:
	int _tileNum;
	
	MapManager* map; 

	vector<string> _kitchenWall;
	vector<string> _interiorTile;
	vector<class Tile*> vObjectTile;

	string currentTile;

	void SetTile(vector<string> Tiletype);
	void CreateObjectTile();
	void ClickTile();

public:
	ObjectTile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size); 
	virtual ~ObjectTile();


	virtual void Init();

	virtual void Release();

	virtual void Update();

	virtual void Render();

	void Reset() { currentTile = "None"; }

	vector<class Tile*> GetvObjectTile() { return vObjectTile; }
	string GetCurrentTile() { return currentTile; }
	void SetLinkWithMapManager(MapManager* map) { this->map = map; }

};

