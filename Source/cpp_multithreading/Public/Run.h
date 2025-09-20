// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

//create FRunnable thread

class CPP_MULTITHREADING_API FRun : public FRunnable
{
private:
    // Different types of pointers
    // TUniquePtr<FWeapon> PrimaryWeapon;      // Exclusive ownership
    // TSharedPtr<FWeapon> SharedWeapon;       // Shared ownership
    // TWeakPtr<FWeapon> BackupWeapon;         // Weak reference
    // FWeapon* RawWeapon;                     // Raw pointer (avoid if possible)

    //declare unique pointer
    TUniquePtr<int> Asd1;

    
    TUniquePtr<FThread> Thread_2;  // Automatically cleaned up

    TSharedPtr<FRun> SharedRunnable = MakeShared<FRun>();

    FRun* Runnable= new FRun; //pointer object
    FRunnableThread* Thread = FRunnableThread::Create(Runnable,TEXT("RunnableWork"));

    FRunnableThread* Thread_1;
    
    bool bIsThreadRunning;
    
public:
    FRun()
        : Thread(nullptr)
        , bIsThreadRunning(false)
    {
    }
    
    virtual ~FRun()
    {
        if (Thread)
        {
            Thread->Kill(true);
            delete Thread;
        }
    }

    // Starts the thread
    bool StartThread()
    {
        if (!Thread)
        {
            bIsThreadRunning = true;
            Thread = FRunnableThread::Create(this, TEXT("FRun Thread"));
            return Thread != nullptr;
        }
        return false;
    }

    virtual uint32 Run() override
    {
        while (bIsThreadRunning)
        {
            // Your thread work goes here
            
            
            // Optional: Add sleep to prevent thread from consuming too much CPU
            FPlatformProcess::Sleep(0.01f);
        }
        return 0;
    }

    virtual void Stop() override
    {
        bIsThreadRunning = false;
    }

    virtual void Exit() override
    {
        // Cleanup code here
    }
};


