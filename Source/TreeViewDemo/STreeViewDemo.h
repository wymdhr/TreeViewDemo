// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STableViewBase.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Views/STreeView.h"

class FTreeViewInstanceData
{
public:
	//���ڹ�����ڵ�
	FTreeViewInstanceData(const FString& InPath);

	//���ڹ����ӽڵ�
	FTreeViewInstanceData(const FString& InPath, TSharedPtr<FTreeViewInstanceData>&InParent);

	//�����Ŀ��־��Icon����������Ŀ¼�����ļ�
	TSharedPtr<SWidget> CreateIcon() const;

public:
	// Ŀ��·��
	FString DiskPath;

	// ·���������֣���D:\Program Files (x86)\PVS-Studio��Name=PVS-Studio����·��ָ��һ���ļ�����Name�ǲ�����չ�����ļ��� 
	FString CleanName;

	// ��־DiskPathָ�����һ���ļ�����Ŀ¼
	bool bIsDirectory;

	//��¼�˽ڵ��Ӧ�ĸ��ڵ�
	TSharedPtr<FTreeViewInstanceData> Parent;

	//��¼�˽ڵ��Ӧ�������ӽڵ�
	TArray<TSharedPtr<FTreeViewInstanceData>> Children;
};

class STreeViewDemo : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(STreeViewDemo) 
	:_RootPath("")
	{}
		SLATE_ARGUMENT(FString, RootPath)
	SLATE_END_ARGS()
public:
	/** Constructs this widget with InArgs */
	virtual void Construct(const FArguments& InArgs);
	
private:
	typedef TSharedPtr<FTreeViewInstanceData> FTreeViewInstanceItem;
	typedef STreeView<FTreeViewInstanceItem> STreeViewPtr;
	//���ݸ�Ŀ¼·����ʼ��TreeRootItems
	void InitTreeView(const FString& InRootPath);

	void ConstructChildrenRecursively(FTreeViewInstanceItem TreeItem);

	//����TreeItem�ĺ���
	TSharedRef<ITableRow> GenerateTreeRow(FTreeViewInstanceItem TreeItem, const TSharedRef<STableViewBase>& OwnerTable);

	//��ȡĳ���ڵ���ӽڵ���Ϣ
	void GetChildrenForTree(FTreeViewInstanceItem TreeItem, TArray< FTreeViewInstanceItem >& OutChildren);
private:
	//ʵ�ʵ�TreeView
	TSharedPtr<STreeViewPtr> TreeViewPtr;

	//�������и��ڵ������
	TArray<FTreeViewInstanceItem> TreeRootItems;
};
