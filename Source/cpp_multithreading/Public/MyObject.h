// Fill out your copyright notice in the Description page of Project Settings.
// .h
#pragma once
#include "CoreMinimal.h"

class FMyThread : public FRunnable {
	FMyThread( /*Parameters*/) {
		Thread = FRunnableThread::Create(this, TEXT("MyThread"));
	};

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
	virtual void Stop() override;

	FRunnableThread* Thread;
	bool bShutdown = false;
};


 
