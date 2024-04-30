// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGame/InputPlayer/AFood.h"

// Sets default values
AAFood::AAFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAFood::BeginPlay()
{
	Super::BeginPlay();
	
}
void AAFood::Interact(AASnakeSpline* snake)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("exav"));
	}
	snake->AddNewElement();
	this->Destroy();
}




