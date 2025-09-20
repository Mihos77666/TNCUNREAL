// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor_1.h"

// Sets default values
AMyActor_1::AMyActor_1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMyActor_1::MyInterfaceFunction_Implementation(int32 MyInt2)
{
	 
}


int AMyActor_1::MyLambdaFunction_Implementation(int32 A)
{
	//use MyEnum
	
	return 10;
}

// Called when the game starts or when spawned
void AMyActor_1::BeginPlay()
{
	Super::BeginPlay();
	
}




void AMyActor_1::SpawnActor()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->SpawnActor<AMyActor_1>();
	}	
}

TArray<FVector> AMyActor_1::CalcA()
{
	TArray<FVector> A;
	A.Add(FVector(1,2,3));
	A.Add(FVector(4,5,6));
	return A;
	
}

struct MyStruct
{
	int32 MyIntA {89};
	int *ptr {nullptr};
	int32 MyIntB {99};
	double MyDouble {99.99};
	
};



 



