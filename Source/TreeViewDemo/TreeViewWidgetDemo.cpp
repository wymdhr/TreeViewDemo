// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TreeViewWidgetDemo.h"
#include "STreeViewDemo.h"

UTreeViewWidget::UTreeViewWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TSharedRef<SWidget> UTreeViewWidget::RebuildWidget()
{
	return SNew(STreeViewDemo)
		.RootPath(CurrentRootPath);
}
