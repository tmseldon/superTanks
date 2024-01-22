// Fill out your copyright notice in the Description page of Project Settings.


#include "StartInfoViewModel.h"

void UStartInfoViewModel::SetMessageStart(FText NewText)
{
    if (UE_MVVM_SET_PROPERTY_VALUE(MessageStart, NewText))
    {
        // Notify GetModifiedMessage()
        UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetModifiedMessage);
    }
}

FText UStartInfoViewModel::GetMessageStart() const
{
	return MessageStart;
}

// Just a testing method to test how to propagate the change on binding property through method
// To check that is working we add a _MOD text at the end of the text
FText UStartInfoViewModel::GetModifiedMessage() const
{
    if (!MessageStart.IsEmpty())
    {
        FString MessageModified = MessageStart.ToString() + "_MOD";
        return FText::FromString(MessageModified);
    }

    return FText::GetEmpty();
}
