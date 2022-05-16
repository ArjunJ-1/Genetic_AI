// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DNA.h"
#include "EvolutionActor.generated.h"

#define NUM_POPULATION (1000)

UCLASS()
class GENETIC_AI_API AEvolutionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEvolutionActor();

	TArray<DNA> M_Population;

	TArray<DNA> ChildGeneration();
	void GeneratePopulation(TArray<DNA> newChildren = TArray<DNA>());

	int M_NumberOfGenerations = 0;
	int M_HighestFitness = 0;
	FString M_HighestFitnessPhrase;

	bool Elitism = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
