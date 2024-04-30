// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SnakeGame/InputPlayer/InteractInterface.h"

#include "AFood.generated.h"

UCLASS()
class SNAKEGAME_API AAFood : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAFood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	virtual void Interact(AASnakeSpline* snake) override;


};
	