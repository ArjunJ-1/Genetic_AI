// Fill out your copyright notice in the Description page of Project Settings.


#include "DNA.h"

DNA::DNA()
{
	M_GeneratedPhrase.Empty();
	Generate();
}

DNA::DNA(bool ShouldGenerate)
{
	M_GeneratedPhrase.Empty();
	if (ShouldGenerate) {
		Generate();
	}
}

DNA::~DNA()
{
}

void DNA::Generate() {
	TArray<char> UsableChars = GenerateUsableCharacters();
	for (int i = 0; i < NUM_CHARACTERS; i++) {
		AddCharToGeneratedPhrase(UsableChars[FMath::RandRange(0, UsableChars.Num() - 1)]);
	}
}

TArray<char> DNA::GenerateUsableCharacters() {
	TArray<char> UsableChars;
	UsableChars.Add('A');
	UsableChars.Add('B');
	UsableChars.Add('C');
	UsableChars.Add('D');
	UsableChars.Add('E');
	UsableChars.Add('F');
	UsableChars.Add('G');
	UsableChars.Add('H');
	UsableChars.Add('I');
	UsableChars.Add('J');
	UsableChars.Add('K');
	UsableChars.Add('L');
	UsableChars.Add('M');
	UsableChars.Add('N');
	UsableChars.Add('O');
	UsableChars.Add('P');
	UsableChars.Add('Q');
	UsableChars.Add('R');
	UsableChars.Add('S');
	UsableChars.Add('T');
	UsableChars.Add('U');
	UsableChars.Add('V');
	UsableChars.Add('W');
	UsableChars.Add('X');
	UsableChars.Add('Y');
	UsableChars.Add('Z');
	UsableChars.Add(' ');

	return UsableChars;
}

void DNA::AddCharToGeneratedPhrase(char Val) {
	M_GeneratedPhrase.AppendChar(Val);
}

int DNA::CalculateAndStoreFitness() {
	int RetVal = 0;

	if (M_StoredFitness == -1) {
		M_StoredFitness = 0; //first time calculating fitness

		for (int i = 0; i < M_GeneratedPhrase.Len(); i++) {
			if (M_GeneratedPhrase.GetCharArray()[i] == TARGET_PHRASE[i]) {
				RetVal++;
			}
		} 
		M_StoredFitness = RetVal; //stored fitness for next time
	}
	else {
		RetVal = M_StoredFitness; //already calculated before, use the stored value
	}
	return RetVal;
}

DNA DNA::Crossover(DNA OtherDNA) {
	DNA RetVal = DNA(false);

	const int MinVal = 3;
	const int MidIndex = FMath::RandRange(MinVal, NUM_CHARACTERS - MinVal);
	const int CrossoverSize = NUM_CHARACTERS - MidIndex;

	for (int i = 0; i < NUM_CHARACTERS; i++) {
		if (i < CrossoverSize) {
			ensureAlways(M_GeneratedPhrase.Len() > 0);
			RetVal.AddCharToGeneratedPhrase(M_GeneratedPhrase.GetCharArray()[i]);
		}
		else {
			ensureAlways(OtherDNA.M_GeneratedPhrase.Len() > 0);
			RetVal.AddCharToGeneratedPhrase(OtherDNA.M_GeneratedPhrase.GetCharArray()[i]);
		}
	}

	return RetVal;
}

void DNA::Mutation() {
	TArray<char> UsableChars = GenerateUsableCharacters();

	for (int i = 0; i < M_GeneratedPhrase.Len(); i++) {
		if (FMath::RandRange(0.0f, 1.0f) < MUTATION_CHAR_CHANCE) {
			ensureAlways(M_GeneratedPhrase.Len() > 0);
			M_GeneratedPhrase.GetCharArray()[i] = UsableChars[FMath::RandRange(0, UsableChars.Num() - 1)];
		}
	}
}