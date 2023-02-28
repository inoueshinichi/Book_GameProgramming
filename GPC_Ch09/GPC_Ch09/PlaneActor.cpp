//
//  PlaneActor.cpp
//  GPC_Ch09
//
//  Created by Inoue Shinichi on 2022/08/18.
//

#include "PlaneActor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "MeshComponent.hpp"

PlaneActor::PlaneActor(Game* game)
    : Actor(game)
{
    SetScale(10.0);
    MeshComponent* mc = new MeshComponent(this);
    mc->SetMesh(GetGame()->GetRenderer()->GetMesh(ASSETS_DIR "Assets/Plane.gpmesh"));
}
