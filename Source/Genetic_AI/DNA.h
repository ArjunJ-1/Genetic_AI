// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define NUM_CHARACTERS (23)
#define TARGET_PHRASE ("EVOLUTIONARY ALGORITHM")
#define MUTATION_CHANCE (0.20f)
#define MUTATION_CHAR_CHANCE (0.10f)

/**
 * 
 */
class GENETIC_AI_API DNA
{
public:
	DNA();
	DNA(bool shouldGenerate);
	~DNA();

	int CalculateAndStoreFitness();
	void AddCharToGeneratedPhrase(char val);

	DNA Crossover(DNA otherDNA);
	void Mutation();

	FString M_GeneratedPhrase;

private:
	int M_StoredFitness = -1;

	void Generate();
	TArray<char> GenerateUsableCharacters();
};
