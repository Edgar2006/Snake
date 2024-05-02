// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SnakeGame/InputPlayer/InputCharacter.h"

#include "Components/Button.h"
#include "UserHUD.generated.h"

/**
 * 
 */




UCLASS(Abstract)
class SNAKEGAME_API UUserHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	AInputCharacter* Player;


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ScorreText;

	UPROPERTY(meta = (BindWidget))
	class UButton* UpButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* DownButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* LeftButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* RightButton;

public:
	void SetScorre(int size);


	UFUNCTION(BlueprintCallable)    
	void MoveInput(FVector vector);

	UFUNCTION(BlueprintCallable)    
	void MoveUp();
	UFUNCTION(BlueprintCallable)    
	void MoveDown();
	UFUNCTION(BlueprintCallable)    
	void MoveLeft();
	UFUNCTION(BlueprintCallable)    
	void MoveRight();
protected:
	virtual bool Initialize();
};
