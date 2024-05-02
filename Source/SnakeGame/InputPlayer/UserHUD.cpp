#include "UserHUD.h"
#include <Kismet/GameplayStatics.h>
// Fill out your copyright notice in the Description page of Project Settings.






void UUserHUD::SetScorre(int size)
{
	this->ScorreText->SetText(FText::AsNumber(size));
}


void UUserHUD::MoveInput(FVector vector)
{
   Player->MoveAction(FInputActionValue(vector));
}

void UUserHUD::MoveUp()
{
   MoveInput(FVector(0,1,0));
}

void UUserHUD::MoveDown()
{
   MoveInput(FVector(0,-1,0));
}

void UUserHUD::MoveLeft()
{
   MoveInput(FVector(-1, 0, 0));
}

void UUserHUD::MoveRight()
{
   MoveInput(FVector(1, 0, 0));
}



bool UUserHUD::Initialize()
{
   bool success = UUserWidget::Initialize();
   if (!success){
      return false;
   }


   Player = (Cast<AInputCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));

   UpButton->OnClicked.AddDynamic(this, &UUserHUD::MoveUp);
   DownButton->OnClicked.AddDynamic(this, &UUserHUD::MoveDown);
   LeftButton->OnClicked.AddDynamic(this, &UUserHUD::MoveLeft);
   RightButton->OnClicked.AddDynamic(this, &UUserHUD::MoveRight);

   
   
   return true;
}
