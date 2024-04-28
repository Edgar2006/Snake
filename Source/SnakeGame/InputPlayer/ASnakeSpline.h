// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASnakeSpline.generated.h"

UCLASS()
class SNAKEGAME_API AASnakeSpline : public AActor
{
	GENERATED_BODY()
	


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TArray<USplineMeshComponent*> ArrSplineMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UStaticMesh* HeadStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UStaticMesh* BodyStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	int Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	int Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	int BodyLenght;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	bool bWithTangent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	int MaxHeap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	int Heap;

protected:
	UFUNCTION(BlueprintCallable)
	void SetSplineMeshBodyTransform(USplineMeshComponent*& SplineMesh, int Iterator);
	
	UFUNCTION(BlueprintCallable)
	void SetSplineMeshTransformWithoutTangent(USplineMeshComponent*& SplineMesh, int Iterator, float OffsetWithElement, FVector Scale);
	
	UFUNCTION(BlueprintCallable)
	void RemoveNoUsedPoints();


public:
	UFUNCTION(BlueprintCallable)
	void Move(FVector Position);

public:	
	// Sets default values for this actor's properties
	AASnakeSpline();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
