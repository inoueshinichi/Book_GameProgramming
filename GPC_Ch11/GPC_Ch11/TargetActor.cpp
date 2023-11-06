//
//  TargetActor.cpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/28.
//

#include "TargetActor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "MeshComponent.hpp"
#include "BoxComponent.hpp"
#include "Mesh.hpp"
#include "TargetComponent.hpp"

TargetActor::TargetActor(Game* game)
    : Actor(game)
{
    // SetScale(10.0f);
    
    SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = GetGame()->GetRenderer()->GetMesh(ASSETS_DIR "Assets/Target.gpmesh");
    
    mc->SetMesh(mesh);
    
    // Add collition box
    BoxComponent* bc = new BoxComponent(this);
    bc->SetObjectBox(mesh->GetBox());
    new TargetComponent(this); // ゲーム終了時に破棄される
}
