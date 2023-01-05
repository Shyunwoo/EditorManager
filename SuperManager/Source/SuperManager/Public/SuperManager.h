// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSuperManagerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	bool CheckIsActorSelectionLocked(AActor* ActorToProcess);
	void ProcessLockingForOutliner(AActor* ActorToProcess, bool bShouldLock);

#pragma region ProcessDataForAdvanceDeletionTab

	bool DeleteSingleAssetForAssetList(const FAssetData& AssetDataToDelete);
	bool DeleteMultipleAssetsForAssetList(const TArray<FAssetData>& AssetsToDelete);

	void ListUnusedAssetsForAssetList(const TArray<TSharedPtr<FAssetData>>& AssetsDataToFilter, TArray<TSharedPtr<FAssetData>>& OutUnusedAssetsData);
	void ListSameNameAssetsForAssetList(const TArray<TSharedPtr<FAssetData>>& AssetsDataToFilter, TArray<TSharedPtr<FAssetData>>& OutSameNameAssetsData);
	void SyncCBToClickedAssetForAssetList(const FString& AssetPathYoSync);

#pragma endregion

private:

#pragma region ContentBrowserMenuExtention

	void InitCBMenuExtention();

	TArray<FString> FolderPathsSelected;
	TSharedRef<FExtender> CustomCBMenuExtender(const TArray<FString>& SelectedPaths);

	void AddCBMenuEntry(class FMenuBuilder& MenuBuilder);

	void OnDeleteUnusedAssetButtonClicked();
	void OnDeleteEmptyFoldersButtonClicked();
	void OnAdvanceDeletionButtonClicked();

	void FixUpRedirectors();

#pragma endregion

#pragma region CustomEditorTab

	void RegisterAdvanceDeletionTab();
	
	TSharedRef<SDockTab> OnSpawnAdvanceDeletionTab(const FSpawnTabArgs& SpawnTabArgs);
	TSharedPtr<SDockTab> ConstructedDockTab;

	TArray<TSharedPtr<FAssetData>> GetAllAssetDataUnderSelectedFolder();

	void OnAdvanceDeletionTabClosed(TSharedRef<SDockTab> TabToClose);

#pragma endregion

#pragma region LevelEditorMenuExtension

	void InitLevelEditorExtention();

	TSharedRef<FExtender> CustomLevelEditorMenuExtender(const TSharedRef<FUICommandList> UICommandList, const TArray<AActor*> SelectedActors);

	void AddLevelEditorMenuEntry(class FMenuBuilder& MenuBuilder);

	void OnLockActorSelectionButtonClicked();
	void OnUnlockActorSelectionButtonClicked();
	void RefreshSceneOutliner();

#pragma endregion

#pragma region SelectionLock

	void InitCustomSelectionEvent();

	void OnActorSelected(UObject* SelectedObject);

	void LockActorSelection(AActor* ActorToProcess);
	void UnlockActorSelection(AActor* ActorToProcess);

#pragma endregion

#pragma region CustomEditorUICommands

	TSharedPtr<class FUICommandList> CustomUICommands;

	void InitCustomUICommands();

	void OnSelectionLockHotKeyPressed();
	void OnUnlockActorSelectionHotKeyPressed();

#pragma endregion

#pragma region SceneOutLinerExtension

	void InitSceneOutlinerColumnExtension();

	TSharedRef<class ISceneOutlinerColumn> OnCreateSelectionLockColumn(class ISceneOutliner& Sceneoutliner);

	void UnregisterSceneOutlinerColumnExtension();

#pragma endregion

	TWeakObjectPtr<class UEditorActorSubsystem> WeakEditorActorSubsystem;

	bool GetEditorActorSubsystem();
 };
