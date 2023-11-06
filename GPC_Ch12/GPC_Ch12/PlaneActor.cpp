//
//  PlaneActor.cpp
//  GPC_Ch12
//
//  Created by Inoue Shinichi on 2023/11/01.
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
    
    mBox = new BoxComponent(this);
    mBox->SetObjectBox(mesh->GetBox());
    
    game->AddPlane(this);
}

PlaneActor::~PlaneActor()
{
    GetGame()->RemovePlane(this);
}


