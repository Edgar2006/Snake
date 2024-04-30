// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGame/InputPlayer/AWall.h"

// Sets default values
AAWall::AAWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAWall::Interact(AASnakeSpline* snake)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("merar"));
	}
}


