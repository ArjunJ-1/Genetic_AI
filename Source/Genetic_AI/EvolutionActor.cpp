// Fill out your copyright notice in the Description page of Project Settings.


#include "EvolutionActor.h"
#include "EngineMinimal.h"

#define NUM_PARENTS_PAIR (50)

// Sets default values
AEvolutionActor::AEvolutionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEvolutionActor::BeginPlay()
{
	Super::BeginPlay();
	
	GeneratePopulation();
}

// Called every frame
void AEvolutionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GeneratePopulation(ChildGeneration());

	//see if we have successfully found our target phrase
	for (int i = 0; i < M_Population.Num(); i++) {
		if (M_Population[i].CalculateAndStoreFitness() > M_HighestFitness) {
			M_HighestFitness = M_Population[i].CalculateAndStoreFitness();
			M_HighestFitnessPhrase = M_Population[i].M_GeneratedPhrase;
		}
		if (M_Population[i].CalculateAndStoreFitness() == NUM_CHARACTERS) {
			ensureAlwaysMsgf(false, TEXT("SUCCESS: We Found Our Target Phrase!"));
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, -1, FColor::White, FString::Printf(TEXT("hightestFitness: %d"), M_HighestFitness));
	GEngine->AddOnScreenDebugMessage(-1, -1, FColor::White, FString::Printf(TEXT("hightestFitnessPhrase: %s"), *M_HighestFitnessPhrase));
	GEngine->AddOnScreenDebugMessage(-1, -1, FColor::White, FString::Printf(TEXT("Generation: %d"), M_NumberOfGenerations));
}

void AEvolutionActor::GeneratePopulation(TArray<DNA> NewChildren) {
	if (M_Population.Num() == 0) {
		for (int i = 0; i < NUM_POPULATION; i++) {
			M_Population.Add(DNA());
		}
	}
	else {
		M_Population.Empty();
		M_Population.Append(NewChildren);

		for (int i = 0; i < NUM_POPULATION - NewChildren.Num(); i++) {
			M_Population.Add(DNA());
		}
	}

	M_NumberOfGenerations++;
}

TArray<DNA> AEvolutionActor::ChildGeneration() {
	TArray<DNA> Parents;

	for (int i = 0; i < NUM_PARENTS_PAIR * 2; i++) {
		if (!Elitism) {
			int TotalFitness = 0;

			for (int k = 0; k < M_Population.Num(); k++) {
				TotalFitness += M_Population[k].CalculateAndStoreFitness();
			}

			const int SelectedValue = FMath::RandRange(0, TotalFitness);
			float CurrentValue = 0;

			for (int j = 0; j < M_Population.Num(); j++) {
				CurrentValue += M_Population[j].CalculateAndStoreFitness();
				if (SelectedValue <= CurrentValue) {
					//the dna has been found, and the parent should be stored
					Parents.Add(M_Population[j]);
					//remove the parent from the population
					M_Population.RemoveAt(j);
					break;
				}
			}
		}
		else {
			int HighestFitness = 0;
			int DNAIdx = -1;

			for (int j = 0; j < M_Population.Num(); j++) {
				if (M_Population[j].CalculateAndStoreFitness() > HighestFitness) {
					HighestFitness = M_Population[j].CalculateAndStoreFitness();
					DNAIdx = j;
				}
			}
			if (DNAIdx != -1) {
				//found the highest fitness, store the parent
				Parents.Add(M_Population[DNAIdx]);
				//remove the parent from the population
				M_Population.RemoveAt(DNAIdx);
			}
		}
	}

	//create children
	TArray<DNA> NewChildren;

	for (int i = 0; i < NUM_PARENTS_PAIR; i++) {
		DNA ChildOne = Parents[i * 2 + 0].Crossover(Parents[1]);
		DNA ChildTwo = Parents[i * 2 + 1].Crossover(Parents[0]);

		//possibly mutate them
		if (FMath::RandRange(0.0f, 1.0f) < MUTATION_CHANCE) {
			if (FMath::RandBool()) {
				ChildOne.Mutation();
			}
			else {
				ChildTwo.Mutation();
			}
		}
		NewChildren.Add(ChildOne);
		NewChildren.Add(ChildTwo);
	}
	return NewChildren;
}

