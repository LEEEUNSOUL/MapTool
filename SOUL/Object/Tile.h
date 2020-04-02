#pragma once

enum ATTRIBUTE
{
	AT_WALKUNABLE, 
	NONE
};
class Tile : public GameObject
{
	ClassInherited(GameObject)

public:
	Tile(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~Tile();

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetImg(string imgKey); 
	void SetIndex(POINT pt);

	void SetObjectImg(string imgKey); 

	POINT GetIndex() { return index; }
	string GetImgKey() { return imgKey; }
	
	void SetAttribute(ATTRIBUTE attribute) { this->attribute = attribute; }
	ATTRIBUTE GetAttribute() { return attribute; }


public:
	static void Save(BinaryWriter* w, Tile* tile);
	static void Load(BinaryReader* r, Tile* tile);


private:

	string imgKey;
	string objectKey;
	POINT index;

	shared_ptr<Texture> Img; 
	shared_ptr<Texture> object;

	ATTRIBUTE attribute;

};

