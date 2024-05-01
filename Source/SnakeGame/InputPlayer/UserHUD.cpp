// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeGame/InputPlayer/InputCharacter.h"

#include "SnakeGame/InputPlayer/UserHUD.h"

void UUserHUD::SetScorre(int size)
{
	this->ScorreText->SetText(FText::AsNumber(size));
}

void UUserHUD::NativeConstruct()
{
	Super::NativeConstruct();



}

void UUserHUD::MoveInput()
{
}
