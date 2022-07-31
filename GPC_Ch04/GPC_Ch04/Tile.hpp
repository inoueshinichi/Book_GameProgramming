//
//  Tile.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/04/12.
//

#ifndef Tile_hpp
#define Tile_hpp

#include "Actor.hpp"
#include <vector>

class Game;
class SpriteComponent;

class Tile : public Actor
{
public:
	friend class Grid;
	enum TileState
	{
		EDefault,
		EPath,
		EStart,
		EBase
	};
	
	Tile(Game* game);
	
	void SetTileState(TileState state);
	TileState GetTileState() const { return mTileState; }
	void ToggleSelect();
	const Tile* GetParent() const { return mParent; }
private:
	// 経路探索用
	std::vector<Tile*> mAdjacent;
	Tile* mParent;
	float f;
	float g;
	float h;
	bool mInOpenSet;
	bool mInClosedSet;
	bool mBlocked;
	
	void UpdateTexture();
	SpriteComponent* mSprite;
	TileState mTileState;
	bool mSelected;		
};

#endif /* Tile_hpp */
