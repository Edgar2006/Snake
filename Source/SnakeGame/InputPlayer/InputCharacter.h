// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "Components/CapsuleComponent.h"
#include "SnakeGame/InputPlayer/ASnakeSpline.h"
#include "InputCharacter.generated.h"

UCLASS()
class SNAKEGAME_API AInputCharacter : public ACharacter
{
	GENERATED_BODY()


protected:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* InputMoveAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UCapsuleComponent* HeadCapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	class AASnakeSpline* Snake;


public:
	// Sets default values for this character's properties
	AInputCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveAction(const FInputActionValue& InputValue);



	UFUNCTION(BlueprintCallable)    
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);


};
