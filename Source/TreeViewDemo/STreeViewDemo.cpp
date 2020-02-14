// Fill out your copyright notice in the Description page of Project Settings.


#include "STreeViewDemo.h"
#include "Misc/Paths.h"
#include "EditorStyleSet.h"
#include "Styling/SlateTypes.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "HAL/FileManager.h"

void STreeViewDemo::Construct(const FArguments& InArgs)
{
	InitTreeView(InArgs._RootPath);
	SAssignNew(TreeViewPtr, STreeViewPtr)
		.TreeItemsSource(&TreeRootItems)
		.OnGenerateRow(this, &STreeViewDemo::GenerateTreeRow)
		.ItemHeight(30)
		.SelectionMode(ESelectionMode::Multi)
		.OnGetChildren(this, &STreeViewDemo::GetChildrenForTree)
		.ClearSelectionOnClick(false)
		.HighlightParentNodesForSelection(true);
	this->ChildSlot
		[
			TreeViewPtr.ToSharedRef()
		];
}

void STreeViewDemo::InitTreeView(const FString& InRootPath)
{
	FTreeViewInstanceItem Root = FTreeViewInstanceItem(new FTreeViewInstanceData(InRootPath));
	TreeRootItems.Add(Root);
	ConstructChildrenRecursively(Root);
}

void STreeViewDemo::ConstructChildrenRecursively(FTreeViewInstanceItem TreeItem)
{
	if (TreeItem.IsValid())
	{
		//�ҵ���Ŀ¼�������ļ�
		TArray<FString> FindedFiles;
		FString SearchFile = TreeItem->DiskPath + "/*.*";
		IFileManager::Get().FindFiles(FindedFiles, *SearchFile, true, true);

		for (auto&element : FindedFiles)
		{
			//�����ӽڵ�
			FString FullPath = TreeItem->DiskPath + "/" + element;
			FTreeViewInstanceItem Child = FTreeViewInstanceItem(new FTreeViewInstanceData(FullPath, TreeItem));
			TreeItem->Children.Add(Child);
			if (Child->bIsDirectory)
			{
				//Ŀ¼��ݹ��ȡ���ӽڵ���Ϣ
				ConstructChildrenRecursively(Child);
			}
		}
	}
}

TSharedRef<ITableRow> STreeViewDemo::GenerateTreeRow(FTreeViewInstanceItem TreeItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	check(TreeItem.IsValid());
	//����TreeItem����һ��Item���ֵ�Widget
	return
		SNew(STableRow<FTreeViewInstanceItem>, OwnerTable)
		[
			SNew(SBox)
			.WidthOverride(200.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
					TreeItem->CreateIcon().ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
				SNew(STextBlock)
				.Text(FText::FromString(TreeItem->CleanName))
				.Font(FStyleDefaults::GetFontInfo(20))
				]
			]
		];
}

void STreeViewDemo::GetChildrenForTree(FTreeViewInstanceItem TreeItem, TArray< FTreeViewInstanceItem >& OutChildren)
{
	//��ȡTreeItem���ӽڵ���Ϣ
	if (TreeItem.IsValid())
	{
		OutChildren = TreeItem->Children;
	}
}

FTreeViewInstanceData::FTreeViewInstanceData(const FString& InPath)
	:DiskPath(InPath)
{
	CleanName = FPaths::GetBaseFilename(DiskPath);
	bIsDirectory = !FPaths::FileExists(DiskPath);
}

FTreeViewInstanceData::FTreeViewInstanceData(const FString& InPath, TSharedPtr<FTreeViewInstanceData>&InParent)
	:DiskPath(InPath), Parent(InParent)
{
	CleanName = FPaths::GetBaseFilename(DiskPath);
	bIsDirectory = !FPaths::FileExists(DiskPath);
}

TSharedPtr<SWidget> FTreeViewInstanceData::CreateIcon() const
{
	FSlateColor IconColor = FSlateColor::UseForeground();
	const FSlateBrush* Brush = FEditorStyle::GetBrush(bIsDirectory ? "ContentBrowser.AssetTreeFolderOpen" : "ContentBrowser.ColumnViewAssetIcon");
	return SNew(SImage)
		.Image(Brush)
		.ColorAndOpacity(IconColor);
}
