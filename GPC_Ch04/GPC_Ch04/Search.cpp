//
//  Search.cpp
//  GPC_Ch04
//
//  Created by Inoue Shinichi on 2022/03/21.
//

//#include <list>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

#include <iostream>

struct GraphNode
{
    // 各ノードは隣接ノードへのポインタを持つ
    std::vector<GraphNode*> mAdjacent;
};


struct Graph
{
    // グラフはノードを含む
    std::vector<GraphNode*> mNodes;
};



/* 重み付きグラフでは、個々のノードは隣接ノードへのポインタではなく、
   ノードから出ていくエッジのリストになる.
 */
struct WeightedGraphNode;
struct WeightedEdge
{
    // エッジにつながっているノード
    struct WeightedGraphNode* mFrom;
    struct WeightedGraphNode* mTo;
    // エッジの重み
    float mWeight;
};


struct WeightedGraphNode
{
    // このノードから出ていくエッジを格納
    std::vector<WeightedEdge*> mEdges;
};


struct WeightedGraph
{
    std::vector<WeightedGraphNode*> mNode;
};


// ///////
// 経路探索
// ///////

/* 幅優先探索(BFS) = 最短経路探索(重みを考慮しない) */

// 探索結果を入れる連想配列 (初期状態はkeyのみにノードが入っており, valueはnullptrとなっている. 探索済みのノードには親ノードのポインタが入る.)
using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;

// 幅優先探索
bool BFS(const Graph& graph,
         const GraphNode* start,
         const GraphNode* goal,
         NodeToParentMap& outMap)
{
    bool pathFound = false;
    std::queue<const GraphNode*> q;
    
    q.emplace(start);
    
    while (!q.empty())
    {
        const GraphNode* current = q.front();
        q.pop();
        
        if (current == goal)
        {
            pathFound = true;
            break;
        }
        
        /*ノードを評価して次のノードを決める*/
        for (const GraphNode* node : current->mAdjacent)
        {
            const GraphNode* parent = outMap[node];
            if (parent == nullptr && node != start) // 探索済みノードならば、親ノードにnullptr以外のポインタ値が入る.)
            {
                outMap[node] = current; // 自分を親として追加
                q.emplace(node); // 次の訪問候補に追加
            }
        }
    }
    
    return pathFound;
}


/* GBFS(欲張り最良優先探索) = 次に評価するノードが
 貪欲法(ヒューリスティック関数h(x)により決まる */
struct GBFSScratch // ノードの付随データ
{
    const WeightedEdge* mParentEdge = nullptr; // 親エッジ
    float mHeuristic = 0.0f; // ヒューリスティック値
    bool mInOpenSet = false; // オープンセット(訪問予定集合)に帰属
    bool mInClosedSet = false; // クローズドセット(訪問済み集合)に帰属
};

// 探索結果を入れる連想配列 (初期状態はkeyのみにノードが入っており, valueはnullptrとなっている. 探索済みのノードには親ノードのポインタが入る.)
using GBFSMap = std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

float ComputeHeuristic(const WeightedGraphNode* a, const WeightedGraphNode* b)
{
    return 0.0f;
}

/*欲張り最良(幅優先)探索 エッジの重みは利用しない.*/
bool GBFS(const WeightedGraph& graph,
          const WeightedGraphNode* start,
          const WeightedGraphNode* goal,
          GBFSMap& outMap)
{
    // オープンセット(訪問予定集合)の配列を用意
    std::vector<const WeightedGraphNode*> openSet;
    
    const WeightedGraphNode* current = start;
    outMap[current].mInClosedSet = true; // 始点をクローズドセットに追加
    
    do // ※始点のとき必ず実行するので do~while構文を使っている
    {
        // 隣接ノードをオープンセットに追加する
        for (const WeightedEdge* edge : current->mEdges)
        {
            // 隣接ノードの付随データ(スクラッチ)を取得
            GBFSScratch& data = outMap[edge->mTo];
            
            // クローズドセットに所属していない時
            if (!data.mInClosedSet)
            {
                // 隣接ノードの親エッジを設定する
                data.mParentEdge = edge;
                
                // オープンセットに所属していない時
                if (!data.mInOpenSet)
                {
                    // ヒューリスティックを計算してオープンセットに追加する
                    data.mHeuristic = ComputeHeuristic(edge->mTo, goal);
                    data.mInOpenSet = true;
                    openSet.emplace_back(edge->mTo);
                }
            }
            
            // | 訪問予定集合 | 訪問済み集合 | 実行内容
            // | false      | false     | ヒューリスティック値を計算 & 訪問予定集合に所属する
            // | true       | false     | 何もしない
            // | false      | true      | - (始点)
            // | true       | true      | 何もしない (探索済みの親ノード)
                     
        } // ここのループ終了時に隣接ノードをすべてチェックしているので幅優先探索になっている.
        
        // オープンセットが空=始点から終点までのPathが存在しない場合
        if (openSet.empty())
        {
            break; // 外側のループに出る
        }
        
        
        // オープンセットのうち、コストが最も低いノードを見つける.
        auto iter = std::min_element(openSet.begin(),
                                     openSet.end(),
                                     [&outMap] (const WeightedGraphNode* a, const WeightedGraphNode* b)
        {
            return outMap[a].mHeuristic < outMap[b].mHeuristic;
        });
        
        // それをカレントノードにして、オープンセットからクローズドセットに移す.
        current = *iter;
        openSet.erase(iter);
        outMap[current].mInOpenSet = false;
        outMap[current].mInClosedSet = true;
        
        
        
    } while (current != goal); // ゴールに到達したら終了.
    
    // 経路を見つけたか?
    return (current == goal) ? true : false;
}



/* A*探索
   GBFSは最適な経路を保証できない. この点を改善したアルゴリズム.
   A*では開始ノードから各ノードまでの実際のコストである経路コスト(path-cost)が追加される.
   あるノードxの経路コスト=g(x). A*はf(x)=h(x)+g(x)が最小のノードを次探索ノードに決定する.
 */
struct AStarScratch
{
    const WeightedEdge* mParentEdge = nullptr; // 親エッジ
    float mActuralFromStart = 0.0f; // A*独自: 始点からの経路コスト g(x)
    float mHeuristic = 0.0f; // ヒューリスティック値 h(x)
    bool mInOpenSet = false; // オープンセット(訪問予定集合)に帰属
    bool mInClosedSet = false; // クローズドセット(訪問済み集合)に帰属
};

using AStarMap = std::unordered_map<const WeightedGraphNode*, AStarScratch>;

bool AStar(const WeightedGraph* graph,
           const WeightedGraphNode* start,
           const WeightedGraphNode* goal,
           AStarMap& outMap)
{
    // オープンセット(訪問予定)の配列を用意
    std::vector<const WeightedGraphNode*> openSet;
    
    // 始点
    const WeightedGraphNode* current = start;
    outMap[start].mInClosedSet = true;
    
    do
    {
        for (const WeightedEdge* edge : current->mEdges)
        {
            // 訪問予定ノードのデータ
            AStarScratch& data = outMap[edge->mTo];
            
            // 隣接ノードがクローズドセットに入っていなければ
            if (!data.mInClosedSet)
            {
                // 隣接ノードがオープンセットに入っていなければ
                if (!data.mInOpenSet)
                {
                    data.mParentEdge = edge;
                    // 経路コスト値g(x)を計算
                    data.mActuralFromStart = edge->mWeight + outMap[current].mActuralFromStart;
                    // ヒューリスティック値h(x)を計算
                    data.mHeuristic = ComputeHeuristic(edge->mTo, goal);
                    data.mInOpenSet = true;
                    openSet.emplace_back(edge->mTo);
                }
                else
                {
                    /* クローズセットに無所属で、既にオープンセットに所属しているノードについては、経路コストについて緩和処理を実行 */
                    
                    // カレントを親にした時の経路コストを計算
                    float pathCost = outMap[current].mActuralFromStart + edge->mWeight;
                    if (pathCost < data.mActuralFromStart)
                    {
                        // 経路コストを更新
                        outMap[current].mActuralFromStart = pathCost;
                        // 親エッジを付け替え(ノード選択)
                        outMap[current].mParentEdge = edge;
                    }
                }
            }
            
            // | 訪問予定集合 | 訪問済み集合 | 実行内容
            // | false      | false     | ヒューリスティック値と経路コスト値を計算 & 訪問予定集合に所属する
            // | true       | false     | 経路コスト値に関する緩和処理
            // | false      | true      | - (始点)
            // | true       | true      | 何もしない (探索済みの親ノード)
        } // 隣接ノードに対してオープンセットの追加完了
        
        // 経路がなければ終了
        if (openSet.empty()) break;
        
        // Min f(x) = h(x) + g(x)　なるノードを次の最適ノードに選択する
        auto iter = std::min_element(openSet.begin(),
                                     openSet.end(),
                                     [&outMap] (const WeightedGraphNode* a, const WeightedGraphNode* b)
        {
            float fa = outMap[a].mHeuristic + outMap[a].mActuralFromStart;
            float fb = outMap[b].mHeuristic + outMap[b].mActuralFromStart;
            
            return fa < fb;
        });
        
        // 現在のノードをカレントノードに更新 & オープンセットから削除 & カレントノードをクローズセットに追加
        current = *iter;
        openSet.erase(iter);
        outMap[current].mInClosedSet = true;
        outMap[current].mInOpenSet = false;
        
    } while (current != goal);
    
    return (current == goal) ? true : false;
}



/* ------------- テスト ------------- */


void testBFS()
{
    Graph g;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            GraphNode* node = new GraphNode();
            g.mNodes.emplace_back(node);
        }
    }
    
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            GraphNode* node = g.mNodes[i * 5 + j];
            if (i > 0)
            {
                node->mAdjacent.emplace_back(g.mNodes[(i - 1) * 5 + j]);
            }
            if (i < 4)
            {
                node->mAdjacent.emplace_back(g.mNodes[(i + 1) * 5 + j]);
            }
            if (j > 0)
            {
                node->mAdjacent.emplace_back(g.mNodes[i * 5 + (j - 1)]);
            }
            if (j < 4)
            {
                node->mAdjacent.emplace_back(g.mNodes[i * 5 + (j + 1)]);
            }
        }
    }
    
    NodeToParentMap map;
    bool found = BFS(g, g.mNodes[0], g.mNodes[9], map);
    std::cout << found << '\n';
}


void testHeuristic(bool useAStar)
{
    
}
