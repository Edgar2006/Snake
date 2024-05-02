// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGame/InputPlayer/ASnakeSpline.h"

// Sets default values
AASnakeSpline::AASnakeSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline component");
	HeadStaticMesh = CreateDefaultSubobject<UStaticMesh>("Head SM");
	BodyStaticMesh = CreateDefaultSubobject<UStaticMesh>("Body SM");

}

void AASnakeSpline::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);


	for(int i = 0;i < this->Size;i++)
	{

		FString Str = "TAG_Button_UP_" + FString::FromInt(i + 1);
		FName InitialName = (*Str);

		USplineMeshComponent* splineMesh = NewObject<USplineMeshComponent>(this, InitialName);
		ArrSplineMeshComponent.Add(splineMesh);
		splineMesh->RegisterComponent();
		if(i==0)
		{
			splineMesh->SetStaticMesh(HeadStaticMesh);
		}
		else
		{
			splineMesh->SetStaticMesh(BodyStaticMesh);
		}
		splineMesh->SetMobility(EComponentMobility::Movable);
		splineMesh->SetWorldLocation(FVector(0,0,0));
		splineMesh->SetWorldRotation(FRotator(0,0,0));
		splineMesh->SetRelativeScale3D(FVector(1,1,1));
		splineMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		splineMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AASnakeSpline::SetSplineMeshBodyTransform(USplineMeshComponent*& SplineMesh, int Iterator)
{
	float StartDistance = (this->SplineComponent->GetSplineLength()) - Iterator * this->Offset;
	float EndDistance = (this->SplineComponent->GetSplineLength()) - (Iterator - 1) * this->Offset;
	FVector StartLoc = this->SplineComponent->GetLocationAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local);
	FVector EndLoc = this->SplineComponent->GetLocationAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local);
	FVector StartTang = this->SplineComponent->GetTangentAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local);
	FVector EndTang = this->SplineComponent->GetTangentAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local);
	SplineMesh->SetStartAndEnd(StartLoc, StartTang, EndLoc, EndTang);
}

void AASnakeSpline::SetSplineMeshTransformWithoutTangent(USplineMeshComponent*& SplineMesh, int Iterator, float OffsetWithElement, FVector Scale)
{

	float distance = (this->SplineComponent->GetSplineLength()) - Iterator * OffsetWithElement;
	FTransform NewTransform = this->SplineComponent->GetTransformAtDistanceAlongSpline(distance, ESplineCoordinateSpace::Local, false);
	NewTransform.SetScale3D(Scale);
	SplineMesh->SetRelativeTransform(NewTransform);

}

void AASnakeSpline::RemoveNoUsedPoints()
{
	while (this->SplineComponent->GetDistanceAlongSplineAtSplinePoint(1) < this->SplineComponent->GetSplineLength() - Size * Offset && this->SplineComponent->GetNumberOfSplinePoints() > 3)
	{
		this->SplineComponent->RemoveSplinePoint(0, true);
	}
}




void AASnakeSpline::Move(FVector Position, FVector ForwardVector)
{


	if(this->SecondForwardVector==ForwardVector)
	{
		int splineSize = this->SplineComponent->GetNumberOfSplinePoints();
		this->SplineComponent->SetLocationAtSplinePoint(splineSize-1,Position,ESplineCoordinateSpace::World,true);
	}
	else
	{
		this->SplineComponent->AddSplinePoint(Position, ESplineCoordinateSpace::World, true);
		this->SplineComponent->SetSplinePointType(this->SplineComponent->GetNumberOfSplinePoints()-2,ESplinePointType::Linear, true);
	}


	this->SecondForwardVector = ForwardVector;
	for(int i = 0;i<this->ArrSplineMeshComponent.Num();i++)
	{
		if(i==0)
		{
			SetSplineMeshTransformWithoutTangent(this->ArrSplineMeshComponent[i],i, this->Offset, FVector(1,1,1));
		}
		else
		{
			if(bWithTangent)
			{
				SetSplineMeshBodyTransform(this->ArrSplineMeshComponent[i], i);
			}
			else
			{
				SetSplineMeshTransformWithoutTangent(this->ArrSplineMeshComponent[i],i, this->BodyLenght, FVector(1,1,1));
			}
		}
	}

	if(this->Heap == this->MaxHeap)
	{
		this->Heap = 0;
		RemoveNoUsedPoints();
	}
	else
	{
		this->Heap++;
	}


}

void AASnakeSpline::AddNewElement()
{
	this->Size++;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("avel"));

	FString Str = "TAG_Button_UP_" + FString::FromInt(this->Size);
	FName InitialName = (*Str);

	USplineMeshComponent* splineMesh = NewObject<USplineMeshComponent>(this, InitialName);
	this->ArrSplineMeshComponent.Add(splineMesh);
	splineMesh->RegisterComponent();
	splineMesh->SetMobility(EComponentMobility::Movable);
	splineMesh->SetStaticMesh(BodyStaticMesh);	
	splineMesh->SetWorldLocation(FVector(0,0,0));
	splineMesh->SetWorldRotation(FRotator(0,0,0));
	splineMesh->SetRelativeScale3D(FVector(1,1,1));
	splineMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	splineMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

int AASnakeSpline::GetSize()
{
	return this->Size;
}


// Called when the game starts or when spawned
void AASnakeSpline::BeginPlay()
{
	Super::BeginPlay();
}

