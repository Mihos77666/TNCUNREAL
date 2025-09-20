#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "Camera/CameraComponent.h"
#include "MyActor_1.generated.h"

UCLASS()
class CPP_MULTITHREADING_API AMyActor_1 : public AActor,public IMyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor_1();

	//ovveride function form the interface
	virtual void MyInterfaceFunction_Implementation(int32 InMyInt) override;

	// Note the _Implementation suffix
	virtual int MyLambdaFunction_Implementation(int32 A) override;

	
	UCameraComponent * Camera {} ;
	
	UFUNCTION(blueprintCallable, Category = "Abilities")
	void SpawnActor();

	UFUNCTION(blueprintCallable, Category = "Abilities")
	TArray<FVector> CalcA();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorBPToSpawn;
		
	UPROPERTY
	(EditAnywhere, BlueprintReadWrite, Category = "MyActor_1")
	int32 MyInt{99};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor_1")
	float MyFloat{99.99};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor_2")
	float MyFloat2{34.00};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor_1")
	FVector2D MyVector2D2{1,2};

	//declare vector3D array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVectors")
	TArray<FVector> MyVectors {FVector(1.0f, 1.0f, 1.0f), FVector(2.0f, 2.0f, 2.0f)};
		
	//add component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor_1")
	class UStaticMeshComponent* MyMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyActor_1")
	class UActorComponent* MyActorComponent2;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	 

};