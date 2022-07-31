//
//  Tile.cpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/04/12.
//

#include "Tile.hpp"
#include "SpriteComponent.hpp"
#include "Game.hpp"

Tile::Tile(Game* game)
	: Actor(game)
	, mParent(nullptr)
	, f(0.0f)
	, g(0.0f)
	, h(0.0f)
	, mBlocked(false)
	, mSprite(nullptr)
	, mTileState(EDefault)
	, mSelected(false)
{
	mSprite = new SpriteComponent(this);
	UpdateTexture();
}

void Tile::SetTileState(TileState state)
{
	mTileState = state;
	UpdateTexture(); // タイルのテクスチャを決める
}

void Tile::ToggleSelect()
{
	mSelected = !mSelected;
	UpdateTexture();
}

void Tile::UpdateTexture()
{
	std::string text;
	switch (mTileState)
	{
		case EStart:
			text = ASSET_DIR "Assets/TileTan.png";
			break;
		case EBase:
			text = ASSET_DIR "Assets/TileGreen.png";
			break;
		case EPath:
			if (mSelected)
				text = ASSET_DIR "Assets/TileGreySelected.png";
			else
				text = ASSET_DIR "Assets/TileGrey.png";
			break;
		case EDefault:
		default:
			if (mSelected)
                text = ASSET_DIR "Assets/TileBrownSelected.png";
			else
				text = ASSET_DIR "Assets/TileBrown.png";
			break;
	}
	mSprite->SetTexture(GetGame()->GetTexture(text));
}
