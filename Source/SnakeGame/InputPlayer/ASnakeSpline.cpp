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


	for(int i = 0;i < Size;i++)
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
	float StartDistance = (SplineComponent->GetSplineLength()) - Iterator * this->Offset;
	float EndDistance = (SplineComponent->GetSplineLength()) - (Iterator - 1) * this->Offset;
	FVector StartLoc = SplineComponent->GetLocationAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local);
	FVector EndLoc = SplineComponent->GetLocationAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local);
	FVector StartTang = SplineComponent->GetTangentAtDistanceAlongSpline(StartDistance, ESplineCoordinateSpace::Local);
	FVector EndTang = SplineComponent->GetTangentAtDistanceAlongSpline(EndDistance, ESplineCoordinateSpace::Local);
	SplineMesh->SetStartAndEnd(StartLoc, StartTang, EndLoc, EndTang);
}

void AASnakeSpline::SetSplineMeshTransformWithoutTangent(USplineMeshComponent*& SplineMesh, int Iterator, float OffsetWithElement, FVector Scale)
{

	float distance = (SplineComponent->GetSplineLength()) - Iterator * OffsetWithElement;
	FTransform NewTransform = SplineComponent->GetTransformAtDistanceAlongSpline(distance, ESplineCoordinateSpace::Local, false);
	NewTransform.SetScale3D(Scale);
	SplineMesh->SetRelativeTransform(NewTransform);

}

void AASnakeSpline::RemoveNoUsedPoints()
{
	while (SplineComponent->GetDistanceAlongSplineAtSplinePoint(0) < SplineComponent->GetSplineLength() - Size*Offset)
	{
		SplineComponent->RemoveSplinePoint(0, true);
	}
}

void AASnakeSpline::Move(FVector Position)
{

	SplineComponent->AddSplinePoint(Position, ESplineCoordinateSpace::World, true);
	for(int i = 0;i<ArrSplineMeshComponent.Num();i++)
	{
		if(i==0)
		{
			SetSplineMeshTransformWithoutTangent(ArrSplineMeshComponent[i],i, Offset, FVector(2,1,1));
		}
		else
		{
			if(bWithTangent)
			{
				SetSplineMeshBodyTransform(ArrSplineMeshComponent[i], i);
			}
			else
			{
				SetSplineMeshTransformWithoutTangent(ArrSplineMeshComponent[i],i, BodyLenght, FVector(1,1,1));
			}
		}
	}

	if(Heap == MaxHeap)
	{
		Heap = 0;
		RemoveNoUsedPoints();
	}
	else
	{
		++Heap;
	}


}


// Called when the game starts or when spawned
void AASnakeSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AASnakeSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

