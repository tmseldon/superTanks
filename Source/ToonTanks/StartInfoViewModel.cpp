// Fill out your copyright notice in the Description page of Project Settings.


#include "StartInfoViewModel.h"

void UStartInfoViewModel::SetMessageStart(FText NewText)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(MessageStart, NewText))
    {
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(MessageStart);
    }
}

FText UStartInfoViewModel::GetMessageStart() const
{
	return MessageStart;
}
