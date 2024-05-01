// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h""
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "UserHUD.generated.h"

/**
 * 
 */




UCLASS(Abstract)
class SNAKEGAME_API UUserHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ScorreText;

	UPROPERTY(meta = (BindWidget))
	class UButton* UP_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* DownButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* LeftButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* RightButton;

public:
	void SetScorre(int size);

	virtual void NativeConstruct() override;


	UFUNCTION(BlueprintCallable)    
	void MoveInput();


};
