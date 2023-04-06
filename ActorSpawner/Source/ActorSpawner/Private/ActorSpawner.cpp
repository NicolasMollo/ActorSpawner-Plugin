// Copyright Epic Games, Inc. All Rights Reserved.

#include "ActorSpawner.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Editor.h"

#define LOCTEXT_NAMESPACE "FActorSpawnerModule"

void FActorSpawnerModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Start module"));
}

void FActorSpawnerModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("End module"));
}

bool FActorSpawnerModule::Exec(UWorld* world, const TCHAR* Cmd, FOutputDevice& Ar) {

	if (FParse::Command(&Cmd, TEXT("aiv_instantiateactor"))) {

		TArray<FAssetData> AssetsData;
		GEditor->GetContentBrowserSelections(AssetsData);

		for (const FAssetData& AssetData : AssetsData) {

			UObject* Instance = AssetData.GetAsset();
			UClass* InstanceUClass = Instance->GetClass();

			if (InstanceUClass->IsChildOf(UBlueprint::StaticClass()))
			{
				InstanceUClass = Cast<UBlueprint>(Instance)->GeneratedClass;
				UE_LOG(LogTemp, Error, TEXT("Hei i'm a blueprint!"));

				for (TObjectIterator<UWorld> It; It; ++It)
				{
					UWorld* World = *It;
					UE_LOG(LogTemp, Warning, TEXT("Found world %s"), *World->GetFullName());
					if (World->WorldType == EWorldType::Editor)
					{
						AActor* ActorPtr = World->SpawnActor<AActor>(FVector(0, 0, 100), FRotator());
						World->SpawnActor<AActor>(FVector(0, 0, 100), FRotator());
						World->SpawnActor<AActor>(FVector(0, 0, 200), FRotator());
						World->SpawnActor<AActor>(FVector(0, 0, 300), FRotator());
					}
				}
			}
		}

		return true;

	}

	return false;

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FActorSpawnerModule, ActorSpawner)