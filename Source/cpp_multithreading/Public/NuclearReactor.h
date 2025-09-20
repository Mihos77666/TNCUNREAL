// NuclearReactor.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "NuclearReactor.generated.h"

// Declare reactor types
UENUM(BlueprintType)
enum class EReactorType : uint8
{
    PWR         UMETA(DisplayName = "Pressurized Water Reactor"),
    BWR         UMETA(DisplayName = "Boiling Water Reactor"),
    FastBreeder UMETA(DisplayName = "Fast Breeder Reactor"),
    HTGR        UMETA(DisplayName = "High Temperature Gas Reactor")
};

USTRUCT(BlueprintType)
struct FReactorStats
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PowerOutput = 1000.0f; // MW
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Efficiency = 0.33f; // 33% typical for nuclear
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SafetyRating = 8.0f; // Out of 10
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ConstructionCost = 5000000.0f; // In currency units
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LifespanYears = 60;
};

UCLASS(Blueprintable, BlueprintType)
class CPP_MULTITHREADING_API ANuclearReactor : public AActor
{
    GENERATED_BODY()
    
public:
    ANuclearReactor();

protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reactor")
    UStaticMeshComponent* ReactorMesh;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor")
    EReactorType ReactorType;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor")
    FReactorStats Stats;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor")
    bool bIsOperational = false;

public:
    UFUNCTION(BlueprintCallable, Category = "Reactor")
    virtual void StartReactor();
    
    UFUNCTION(BlueprintCallable, Category = "Reactor")
    virtual void ShutdownReactor();
    
    UFUNCTION(BlueprintCallable, Category = "Reactor")
    virtual float GetCurrentPowerOutput() const;
    
    UFUNCTION(BlueprintPure, Category = "Reactor")
    EReactorType GetReactorType() const { return ReactorType; }
    
    UFUNCTION(BlueprintPure, Category = "Reactor")
    FReactorStats GetStats() const { return Stats; }
    
    // Virtual functions for different reactor behaviors
    UFUNCTION(BlueprintImplementableEvent, Category = "Reactor")
    void OnReactorStarted();
    
    //event
    UFUNCTION(BlueprintImplementableEvent, Category = "Reactor")
    void OnReactorShutdown();
    
    // Friend class for factory access
    friend class UNuclearReactorFactory;

protected:
    virtual void InitializeReactorSpecifics() {}
    
    // Setter for factory use
    void SetReactorStats(const FReactorStats& NewStats) { Stats = NewStats; }
    void SetReactorType(EReactorType NewType) { ReactorType = NewType; }
};