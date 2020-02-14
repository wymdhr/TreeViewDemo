// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Public/Components/Widget.h"
#include "TreeViewWidgetDemo.generated.h"

UCLASS()
class UTreeViewWidget : public UWidget
{
	GENERATED_BODY()

public:
	UTreeViewWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, DisplayName = "Root Directory")
	FString CurrentRootPath;
protected:
	virtual TSharedRef<SWidget> RebuildWidget();
};
