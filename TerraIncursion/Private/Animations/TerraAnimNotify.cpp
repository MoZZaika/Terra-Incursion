// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/TerraAnimNotify.h"

void UTerraAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}