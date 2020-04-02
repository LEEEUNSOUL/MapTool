#pragma once

enum BRUSHTYPE //////鸥老 加己 何咯? 
{
	BRUSHTYPE_NONE,
	WALKUNABLE,
	ERASE
};

class Tile;
class SampleTile; //基敲鸥老  
class ObjectTile; 
class ControlUI; 

class MapManager
{
private:
	static D3DXVECTOR2 IndexToPos(int x, int y);
	static POINT PosToIndex(D3DXVECTOR2 pos);

	int _controltileNum;
	bool isDraw;

	vector<class Tile*> vTile;
	vector<class Tile*> vObjectTile;


	SampleTile* sampleTile;
	ObjectTile* objectTile;

	ControlUI* controlUI;

	shared_ptr<Texture> background;
	shared_ptr<Texture> toolPanel;

	POINT startIndex;
	D3DXVECTOR2 _startDrawPos;

	POINT endIndex;
	D3DXVECTOR2 _endDrawPos;
	FloatRect _toolPanelRc;

	BRUSHTYPE _brushType;
	D3DXCOLOR gridColor;

public:
	static D3DXVECTOR2 tileSize;
	static POINT maxTileNum;

	MapManager();
	~MapManager();

	void Init();
	void Release(); 
	void Update(); 

	void Render(); 
	void UiRender(); 
	//void ImguiRender(); 

	void KeyControl(); 
	void CreateImg(POINT index = {-1, -1}, string messageName = "", string currentTile = "");
	void CreateObjectImg(POINT index, string messageName, string currentTile); 

	void SetBrush();
	void Save(wstring file);
	void Load(wstring file);
	void ReverseNum(POINT startpos, POINT endpos);
	//Control SampleTile
	void ControlTileNum(int num);

	Tile* GetTileAsIndex(POINT index);
	Tile* GetObjectTileAsIndex(POINT index);
	Tile* GetTIleAsPos(D3DXVECTOR2 pos); 
	Tile* GetObjectAsPos(D3DXVECTOR2 pos); 

	int GetControltileNum() { return _controltileNum; }
	BRUSHTYPE GetBrushType() { return _brushType; }
	void SetBrushType(BRUSHTYPE attribute) { _brushType = attribute; }

};