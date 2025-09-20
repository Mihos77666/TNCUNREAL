// NuclearReactorFactory.h
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NuclearReactor.h"
#include "NuclearReactorFactory.generated.h"

UCLASS(BlueprintType, Blueprintable)
class CPP_MULTITHREADING_API UNuclearReactorFactory : public UObject
{
    GENERATED_BODY()
    
public:
    UNuclearReactorFactory();
    
    // Static factory method to create reactors
    UFUNCTION(BlueprintCallable, Category = "Reactor Factory", CallInEditor)
    static ANuclearReactor* CreateReactor(UWorld* World, EReactorType ReactorType, 
                                         const FVector& Location = FVector::ZeroVector,
                                         const FRotator& Rotation = FRotator::ZeroRotator);
    
    // Blueprint callable version that gets world context automatically
    UFUNCTION(BlueprintCallable, Category = "Reactor Factory", CallInEditor)
    static ANuclearReactor* CreateReactorBP(const UObject* WorldContextObject, EReactorType ReactorType,
                                           const FVector& Location = FVector::ZeroVector,
                                           const FRotator& Rotation = FRotator::ZeroRotator);
    
       
    // Get default stats for a reactor type
    UFUNCTION(BlueprintPure, Category = "Reactor Factory")
    static FReactorStats GetDefaultStatsForType(EReactorType ReactorType);
    
    // Get reactor type display name
    UFUNCTION(BlueprintPure, Category = "Reactor Factory")
    static FString GetReactorTypeName(EReactorType ReactorType);
    
    // Batch create multiple reactors
    UFUNCTION(BlueprintCallable, Category = "Reactor Factory", meta = (WorldContext = "WorldContextObject"))
    static TArray<ANuclearReactor*> CreateMultipleReactors(const UObject* WorldContextObject,
                                                          const TArray<EReactorType>& ReactorTypes,
                                                          const TArray<FVector>& Locations);

private:
    // Helper function to configure reactor based on type
    static void ConfigureReactorForType(ANuclearReactor* Reactor, EReactorType ReactorType);
};