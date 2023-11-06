//
//  PlaneActor.cpp
//  GPC_Ch11
//
//  Created by Inoue Shinichi on 2023/07/29.
//

#include "PlaneActor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "MeshComponent.hpp"
#include "BoxComponent.hpp"
#include "Mesh.hpp"

PlaneActor::PlaneActor(Game* game)
    : Actor(game)
{
    SetScale(10.0f);
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh = GetGame()->GetRenderer()->GetMesh(ASSETS_DIR "Assets/Plane.gpmesh");
    mc->SetMesh(mesh);
    
    // Add collision box
    mBox = new BoxComponent(this);
    mBox->SetObjectBox(mesh->GetBox());
    
    game->AddPlane(this);
}

PlaneActor::~PlaneActor()
{
    GetGame()->RemovePlane(this);
}



