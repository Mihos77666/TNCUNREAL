// NuclearReactorFactory.cpp
#include "NuclearReactorFactory.h"
#include "Engine/World.h"

UNuclearReactorFactory::UNuclearReactorFactory()
{
    // Constructor implementation if needed
}

ANuclearReactor* UNuclearReactorFactory::CreateReactor(UWorld* World, EReactorType ReactorType, 
                                                      const FVector& Location, const FRotator& Rotation)
{
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid World provided to CreateReactor"));
        return nullptr;
    }
    
    // Spawn the reactor actor
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    
    ANuclearReactor* NewReactor = World->SpawnActor<ANuclearReactor>(ANuclearReactor::StaticClass(), 
                                                                    Location, Rotation, SpawnParams);
    
    if (NewReactor)
    {
        // Configure the reactor based on its type
        ConfigureReactorForType(NewReactor, ReactorType);
        
        UE_LOG(LogTemp, Warning, TEXT("Created %s reactor at location %s"), 
               *GetReactorTypeName(ReactorType), *Location.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn nuclear reactor"));
    }
    
    return NewReactor;
}

ANuclearReactor* UNuclearReactorFactory::CreateReactorBP(const UObject* WorldContextObject, EReactorType ReactorType,
                                                        const FVector& Location, const FRotator& Rotation)
{
    if (!WorldContextObject)
    {
        return nullptr;
    }
    
    UWorld* World = WorldContextObject->GetWorld();
    return CreateReactor(World, ReactorType, Location, Rotation);
}

FReactorStats UNuclearReactorFactory::GetDefaultStatsForType(EReactorType ReactorType)
{
    FReactorStats Stats;
    
    switch (ReactorType)
    {
        case EReactorType::PWR:
            Stats.PowerOutput = 1000.0f;
            Stats.Efficiency = 0.33f;
            Stats.SafetyRating = 8.5f;
            Stats.ConstructionCost = 5000000.0f;
            Stats.LifespanYears = 60;
            break;
            
        case EReactorType::BWR:
            Stats.PowerOutput = 1200.0f;
            Stats.Efficiency = 0.34f;
            Stats.SafetyRating = 8.0f;
            Stats.ConstructionCost = 4800000.0f;
            Stats.LifespanYears = 60;
            break;
            
        case EReactorType::FastBreeder:
            Stats.PowerOutput = 1500.0f;
            Stats.Efficiency = 0.40f;
            Stats.SafetyRating = 7.5f;
            Stats.ConstructionCost = 8000000.0f;
            Stats.LifespanYears = 80;
            break;
            
        case EReactorType::HTGR:
            Stats.PowerOutput = 600.0f;
            Stats.Efficiency = 0.45f;
            Stats.SafetyRating = 9.0f;
            Stats.ConstructionCost = 3500000.0f;
            Stats.LifespanYears = 40;
            break;
            
        default:
            // Default PWR stats
            break;
    }
    
    return Stats;
}

FString UNuclearReactorFactory::GetReactorTypeName(EReactorType ReactorType)
{
    switch (ReactorType)
    {
        case EReactorType::PWR:
            return TEXT("Pressurized Water Reactor");
        case EReactorType::BWR:
            return TEXT("Boiling Water Reactor");
        case EReactorType::FastBreeder:
            return TEXT("Fast Breeder Reactor");
        case EReactorType::HTGR:
            return TEXT("High Temperature Gas Reactor");
        default:
            return TEXT("Unknown Reactor Type");
    }
}

TArray<ANuclearReactor*> UNuclearReactorFactory::CreateMultipleReactors(const UObject* WorldContextObject,
                                                                       const TArray<EReactorType>& ReactorTypes,
                                                                       const TArray<FVector>& Locations)
{
    TArray<ANuclearReactor*> CreatedReactors;
    
    if (!WorldContextObject)
    {
        return CreatedReactors;
    }
    
    UWorld* World = WorldContextObject->GetWorld();
    if (!World)
    {
        return CreatedReactors;
    }
    
    int32 NumToCreate = FMath::Min(ReactorTypes.Num(), Locations.Num());
    
    for (int32 i = 0; i < NumToCreate; i++)
    {
        ANuclearReactor* NewReactor = CreateReactor(World, ReactorTypes[i], Locations[i]);
        if (NewReactor)
        {
            CreatedReactors.Add(NewReactor);
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Created %d reactors out of %d requested"), 
           CreatedReactors.Num(), NumToCreate);
    
    return CreatedReactors;
}

void UNuclearReactorFactory::ConfigureReactorForType(ANuclearReactor* Reactor, EReactorType ReactorType)
{
    if (!Reactor)
    {
        return;
    }
    
    // Set the reactor type
    Reactor->SetReactorType(ReactorType);
    
    // Set the appropriate stats for this reactor type
    FReactorStats Stats = GetDefaultStatsForType(ReactorType);
    Reactor->SetReactorStats(Stats);
    
    // Set the actor name to include reactor type
    FString ReactorName = FString::Printf(TEXT("%s_%s"), 
                                         *GetReactorTypeName(ReactorType),
                                         *FGuid::NewGuid().ToString().Left(8));
     
}