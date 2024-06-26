// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGame/InputPlayer/InputCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SnakeGame/InputPlayer/InteractInterface.h"
#include "SnakeGame/InputPlayer/UserHUD.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AInputCharacter::AInputCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	HeadCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Snake"));
	HeadCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AInputCharacter::OnHit); 


	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->bUsePawnControlRotation = false;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	

	UserWidget = nullptr;
	UserWidgetClass = nullptr;

}

// Called when the game starts or when spawned
void AInputCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocallyControlled() && UserWidgetClass)
	{
		UserWidget = CreateWidget<UUserHUD>(GetWorld(), UserWidgetClass);
		UserWidget->AddToPlayerScreen();
	}
	UserWidget->SetScorre(Snake->GetSize());

	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC)
	{
		PC->bShowMouseCursor = true; 
		PC->bEnableClickEvents = true; 
		PC->bEnableMouseOverEvents = true;
	}



}

void AInputCharacter::EndPlay(const EEndPlayReason::Type EndPlayerReason)
{
	if(UserWidget)
	{
		UserWidget->RemoveFromParent();
		UserWidget = nullptr;
	}


	Super::EndPlay(EndPlayerReason);
}

// Called every frame
void AInputCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if(IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}
	Snake->Move(this->GetActorLocation() + this->Mesh->GetForwardVector(), this->Mesh->GetForwardVector());
}

// Called to bind functionality to input
void AInputCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
	if(UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(InputMoveAction, ETriggerEvent::Triggered, this, &AInputCharacter::MoveAction);
	}
}

void AInputCharacter::MoveAction(const FInputActionValue& InputValue)
{
	InputVector = InputValue.Get<FVector2D>();
	
}

void AInputCharacter::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if(IInteractInterface* InteractInterface = Cast<IInteractInterface>(OtherActor))
	{
		InteractInterface->Interact(Snake);
		UserWidget->SetScorre(Snake->GetSize());
	}
	else
	{
		
		this->Destroy();
	}
}


