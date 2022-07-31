//
//  Grid.cpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/04/12.
//

#include "Grid.hpp"
#include "Tile.hpp"
#include "Tower.hpp"
#include "Enemy.hpp"
#include <algorithm>

Grid::Grid(Game* game)
    : Actor(game)
    , mSelectedTile(nullptr)
{
    /* ゲーム環境を構築 */
    
    mTiles.resize(NumRows);
    for (size_t i = 0; i < mTiles.size(); ++i)
    {
        mTiles[i].resize(NumCols);
    }
    
    for (size_t i = 0; i < NumRows; ++i)
    {
        for (size_t j = 0; j < NumCols; ++j)
        {
            mTiles[i][j] = new Tile(GetGame());
            mTiles[i][j]->SetPosition(Vector2(TileSize / 2.0f + j * TileSize,
                                              StartY + i * TileSize));
        }
    }
    
    // Start/Endタイルの状態設定
    GetStartTile()->SetTileState(Tile::EStart);
    GetEndTile()->SetTileState(Tile::EBase);
    
    // 隣接リストを設定
    for (size_t i = 0; i < NumRows; ++i)
    {
        for (size_t j = 0; j < NumCols; ++j)
        {
            if (i > 0)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i-1][j]);
            }
            if (i < NumRows - 1)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i+1][j]);
            }
            if (j > 0)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i][j-1]);
            }
            if (j < NumCols - 1)
            {
                mTiles[i][j]->mAdjacent.push_back(mTiles[i][j+1]);
            }
        }
    }
    
    // 経路探索(逆順)
    FindPath(GetEndTile(), GetStartTile());
    UpdatePathTiles(GetStartTile());
    
    mNextEnemy = EnemyTile;
}

void Grid::SelectTile(size_t row, size_t col)
{
    // 有効状態のチェック
    Tile::TileState tstate = mTiles[row][col]->GetTileState();
    if (tstate != Tile::EStart && tstate != Tile::EBase)
    {
        // 一つ前の選択されたタイルを非選択状態に変更
        if (mSelectedTile)
        {
            mSelectedTile->ToggleSelect();
        }
        mSelectedTile = mTiles[row][col];
        mSelectedTile->ToggleSelect();
    }
}

void Grid::ProcessClick(int x, int y)
{
    y -= static_cast<int>(StartY - TileSize / 2);
    if (y >= 0)
    {
        x /= static_cast<int>(TileSize);
        y /= static_cast<int>(TileSize);
        if (x >= 0 && x < static_cast<int>(NumCols) && y >= 0 && y < static_cast<int>(NumRows))
        {
            SelectTile(y, x);
        }
    }
}

// A*経路探索の実装
bool Grid::FindPath(Tile *start, Tile *goal)
{
    // 初期状態をセット
    for (size_t i = 0; i < NumRows; ++i)
    {
        for (size_t j = 0; j < NumCols; ++j)
        {
            mTiles[i][j]->g = 0.0f;
            mTiles[i][j]->mInOpenSet = false;
            mTiles[i][j]->mInClosedSet = false;
        }
    }
    
    std::vector<Tile*> openSet;
    
    // カレントノードにstartを設定, それをクローズセットに追加
    Tile* current = start;
    current->mInClosedSet = true;
    
    do
    {
        // オープンセットに隣接ノードを追加
        for (Tile* neighber : current->mAdjacent)
        {
            // ブロックされていたら無視
            if (neighber->mBlocked)
            {
                continue;
            }
            
            // クローズセットに追加されていない隣接ノードだけをチェック
            if (!neighber->mInClosedSet)
            {
                if (!neighber->mInOpenSet)
                {
                    // オープンセットに属していなければ、その隣接ノードの親をカレントに設定
                    neighber->mParent = current;
                    
                    // 隣接ノードのヒューリスティック値h(x)を設定
                    neighber->h = (neighber->GetPosition() - goal->GetPosition()).Length();
                    
                    // 隣接ノードの経路コストg(x)は親ノードのコスト＋ノードコスト
                    neighber->g = current->g + TileSize;
                    
                    // f(x)=h(x)+g(x)
                    neighber->f = neighber->h + neighber->g;
                    
                    // 隣接ノードをオープンセットに帰属させる
                    openSet.emplace_back(neighber);
                    neighber->mInOpenSet = true;
                }
                else
                {
                    // カレントノードが親ノードになる場合、経路コストg(x)を計算
                    float newG = current->g + TileSize;
                    if (newG < neighber->g)
                    {
                        // このノードを採用
                        neighber->mParent = current;
                        neighber->g = newG;
                        // f(x)を更新
                        neighber->f = neighber->g + neighber->h;
                    }
                }
            }
        }
        
        // オープンセットが空の場合, すべての探索可能性のある経路が消えた
        if (openSet.empty())
        {
            break;
        }
        
        // オープンセット内で最小コストの経路を選択
        auto iter = std::min_element(openSet.begin(), openSet.end(),
                                     [](Tile* a, Tile* b) {
            return a->f < b->f;
        });
        current = *iter; // カレントノードを更新
        openSet.erase(iter);
        current->mInOpenSet = false;
        current->mInClosedSet = true;
        
    } while (current != goal);
    
    return (current == goal) ? true : false;
}

void Grid::UpdatePathTiles(Tile *start)
{
    // すべてのタイルをリセット(start/end除く)
    for (size_t i = 0; i < NumRows; ++i)
    {
        for (size_t j = 0; j < NumCols; ++j)
        {
            if (!(i == 3 && j == 0) && !(i == 3 && j == 15))
            {
                mTiles[i][j]->SetTileState(Tile::EDefault);
            }
        }
    }
    
    // 経路のテクスチャを更新
    Tile* t = start->mParent;
    while (t != GetEndTile())
    {
        t->SetTileState(Tile::EPath);
        t = t->mParent;
    }
}

void Grid::BuildTower()
{
    if (mSelectedTile && !mSelectedTile->mBlocked)
    {
        mSelectedTile->mBlocked = true;
        if (FindPath(GetEndTile(), GetStartTile()))
        {
            Tower* t = new Tower(GetGame());
            t->SetPosition(mSelectedTile->GetPosition());
        }
        else
        {
            // このタワーは経路をブロックする. そのためタワーを作れない
            mSelectedTile->mBlocked = false;
            FindPath(GetEndTile(), GetStartTile());
        }
        UpdatePathTiles(GetStartTile());
    }
}

Tile* Grid::GetStartTile()
{
    return mTiles[3][0];
}

Tile* Grid::GetEndTile()
{
    return mTiles[3][15];
}

void Grid::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    // 新しい敵を出現させる時間はあるか?
    mNextEnemy -= deltaTime;
    if (mNextEnemy <= 0.0f)
    {
        new Enemy(GetGame());
        mNextEnemy += EnemyTile;
    }
}
