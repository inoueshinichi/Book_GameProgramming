//
//  TargetActor.cpp
//  GPC_Ch10
//
//  Created by Inoue Shinichi on 2023/05/30.
//

#include "TargetActor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "MeshComponent.hpp"
#include "BoxComponent.hpp"
#include "Mesh.hpp"

TargetActor::TargetActor(Game* game)
    : Actor(game)
{
    // SetScale(10.0f);
    SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = GetGame()->GetRenderer()->GetMesh(ASSETS_DIR "Assets/Target.gpmesh");
    mc->SetMesh(mesh);
    // Add collision box
    BoxComponent* bc = new BoxComponent(this);
    bc->SetObjectBox(mesh->GetBox());
}


