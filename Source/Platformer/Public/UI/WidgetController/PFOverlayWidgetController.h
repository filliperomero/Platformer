// Copyright Fillipe Romero

#pragma once

#include "CoreMinimal.h"
#include "PFWidgetController.h"
#include "PFOverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChangedSignature, int32, NewValue);

UCLASS()
class PLATFORMER_API UPFOverlayWidgetController : public UPFWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FOnStatChangedSignature OnPlayerCoinsChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnStatChangedSignature OnPlayerLivesChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnStatChangedSignature OnPlayerPointsChangedDelegate;
};
