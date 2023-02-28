//
//  PlaneActor.cpp
//  GPC_Ch06
//
//  Created by Inoue Shinichi on 2022/07/20.
//

#include "PlaneActor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "MeshComponent.hpp"

PlaneActor::PlaneActor(Game* game)
    : Actor(game)
{
    SetScale(10.0f);
    MeshComponent* mc = new MeshComponent(this);
    mc->SetMesh(GetGame()->GetRenderer()->GetMesh(ASSETS_DIR "Assets/Plane.gpmesh"));
}
