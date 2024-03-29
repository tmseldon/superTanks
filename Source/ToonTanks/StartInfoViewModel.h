// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "StartInfoViewModel.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UStartInfoViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess))
	FText MessageStart;

public:
	FText GetMessageStart() const;
	void SetMessageStart(FText NewText);

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetModifiedMessage() const;
};
