// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{

	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Tofromotion(DeltaTime);
	
	// MoveDistance=DistanceMoved;
	FRotator NewRotation = RotationSpeed * DeltaTime;
	AddActorLocalRotation(NewRotation);
}

void AMyActor::Tofromotion(float DeltaTime)
{
	FVector CurrentLocation;

	CurrentLocation = GetActorLocation();
	CurrentLocation += MovementSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);

	if (DestinationReached(CurrentLocation))
	{
		FVector MoveDirection = MovementSpeed.GetSafeNormal2D();
		StartLocation += MoveDistance * MoveDirection;
		SetActorLocation(StartLocation);
		float offset = FVector::Dist(StartLocation, CurrentLocation);
		UE_LOG(LogTemp, Display, TEXT("Log Printing %f"), offset);
		MovementSpeed = -MovementSpeed;
	}
}
bool AMyActor ::DestinationReached(FVector CurrentLocation) const
{
	float DistanceMoved = FVector::Distance(StartLocation, CurrentLocation); // Can also use function Dist instead of Distance
	return DistanceMoved >= MoveDistance;
}