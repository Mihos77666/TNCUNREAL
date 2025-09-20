// NuclearReactor.cpp
#include "NuclearReactor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ObjectMacros.h"

//constructor
ANuclearReactor::ANuclearReactor()
{

    
	// Create and set up the static mesh component
	ReactorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReactorMesh"));
	RootComponent = ReactorMesh;

	// Initialize default values
	bIsOperational = false;
}

void ANuclearReactor::BeginPlay()
{
	Super::BeginPlay();
    
	// Initialize reactor-specific settings
	InitializeReactorSpecifics();
    
	UE_LOG(LogTemp, Warning, TEXT("Nuclear Reactor %s initialized"), *GetName());
}

void ANuclearReactor::StartReactor()
{
	if (!bIsOperational)
	{
		bIsOperational = true;
		UE_LOG(LogTemp, Warning, TEXT("Reactor %s started - Power Output: %.1f MW"), 
			   *GetName(), Stats.PowerOutput);
        
		// Call Blueprint implementable event
		OnReactorStarted();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Reactor %s is already operational"), *GetName());
	}
}

void ANuclearReactor::ShutdownReactor()
{
	if (bIsOperational)
	{
		bIsOperational = false;
		UE_LOG(LogTemp, Warning, TEXT("Reactor %s shutdown"), *GetName());
        
		// Call Blueprint implementable event
		OnReactorShutdown();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Reactor %s is already shut down"), *GetName());
	}
}

float ANuclearReactor::GetCurrentPowerOutput() const
{
	return bIsOperational ? Stats.PowerOutput * Stats.Efficiency : 0.0f;
}