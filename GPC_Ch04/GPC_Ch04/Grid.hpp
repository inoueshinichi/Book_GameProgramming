//
//  Grid.hpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/04/12.
//

#ifndef Grid_hpp
#define Grid_hpp

#include "Actor.hpp"
#include <vector>

class Game;
class Tile;

class Grid : public Actor
{
public:
    Grid(Game* game);
    
    // スクリーン上のx/y位置のマウスクリックを取り扱う
    void ProcessClick(int x, int y);
    
    // 経路探索のためにA*アルゴリズムを使う
    bool FindPath(Tile* start, Tile* goal);
    
    // 塔を建設
    void BuildTower();
    
    // Start/Endのタイルを取得
    Tile* GetStartTile();
    Tile* GetEndTile();
    
    void UpdateActor(float deltaTime) override;
    
private:
    // 特定のタイルを選択
    void SelectTile(size_t row, size_t col);
    
    // 経路上のタイルのテクスチャを更新
    void UpdatePathTiles(Tile* start);
    
    // 現在選択されているタイル
    Tile* mSelectedTile;
    
    // 2次元配列のタイル
    std::vector<std::vector<Tile*>> mTiles;
    
    // 次の敵までの時間
    float mNextEnemy;
    
    // グリッドの行列
    const size_t NumRows = 7;
    const size_t NumCols = 16;
    
    // 左上スタート地点のy座標
    const float StartY = /*250.0f;*/ 192.0f;
    
    // タイルの縦横
    const float TileSize = 64.0f;
    
    // 敵リスポーンの間隔(時間) 1.5sec
    const float EnemyTile = 1.5f;
    
};

#endif /* Grid_hpp */
