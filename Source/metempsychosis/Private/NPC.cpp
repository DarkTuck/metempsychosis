// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Engine/AssetManager.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	//Party=NewObject<UEnemiesToSpawn>(this,PartySubclass);
//	LoadPartyAsset();

	
}

void ANPC::LoadPartyAsset()
{
	// 1) Sprawdźmy, czy PartySubclass ma poprawny SoftObjectPath
	const FSoftObjectPath AssetPath = PartySubclass.ToSoftObjectPath();
	if (!AssetPath.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LoadPartyAsset: PartySubclass path jest niepoprawny lub pusty"));
		return;
	}

	// 2) Wyświetlamy w logu ścieżkę do assetu, który chcemy załadować
	UE_LOG(LogTemp, Warning, TEXT("LoadPartyAsset: rozpoczynam ładowanie %s"), *AssetPath.ToString());

	// 3) Pobieramy referencję do StreamableManagera (możemy użyć tego samego,
	//    którego używa AssetManager, albo utworzyć lokalny, ale lepiej przeciągnąć z AssetManagera)
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

	// 4) Rejestrujemy delegat, który zostanie wywołany po zakończeniu ładowania
	FStreamableDelegate LoadDelegate = FStreamableDelegate::CreateUObject(
		this, &ANPC::OnPartyAssetLoaded
	);

	// 5) Właściwa prośba o asynchroniczne załadowanie (RequestAsyncLoad)
	//    Drugi parametr to priorytet, 0 = normalny; trzeci to czy „blokować” (false = asynchronicznie)
	Streamable.RequestAsyncLoad(
		AssetPath,
		LoadDelegate,
		FStreamableManager::AsyncLoadHighPriority  // możesz wybrać LowPriority lub HighPriority według potrzeb
	);
}

void ANPC::OnPartyAssetLoaded()
{
	// 1) Po zakończeniu ładowania na SoftObjectPtr automatycznie pojawi się obiekt w pamięci,
	//    więc wystarczy zrobić PartySubclass.Get() lub Cast
	UEnemiesToSpawn* LoadedAsset = PartySubclass.Get();
	if (!LoadedAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("OnPartyAssetLoaded: nie udało się pobrać załadowanego assetu z PartySubclass"));
		return;
	}

	// 2) Przechowujemy wskaźnik w zmiennej członkowskiej (żeby Unreal nie wyrzucił tego objektu)
	CachedPartyAsset = LoadedAsset;

	// 3) Logujemy sukces
	UE_LOG(LogTemp, Log, TEXT("OnPartyAssetLoaded: PartyAsset załadowany pomyślnie: %s"), 
		*PartySubclass.ToSoftObjectPath().ToString()
	);

	// 4) (Opcjonalnie) jeśli chcesz wypisać jeszcze jakieś detale, np. z LazyData:
	//    np. możesz użyć CachedPartyAsset->SomeProperty tuż po załadowaniu.

	// 5) (Opcjonalnie) Wyświetl wiadomość na ekranie gry
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			FColor::Green,
			FString::Printf(TEXT("PartyAssetLoaded: %s"), *PartySubclass.ToSoftObjectPath().ToString())
		);
	}
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* ANPC::GetBehaviorTree() const
{
	return BehaviorTree;
}

APatrolPath* ANPC::GetPatrolPath() const
{
	return PatrolPath;
}

TArray<ATBCEnemyBase*> ANPC::GetEnemiesToSpawn() const
{
	return PartySubclass.LoadSynchronous()->GetEnemies();
}

//TArray<ATBCEnemyBase*> ANPC::GetEnemiesToSpawn() const
//{
//	TArray<TSubclassOf<ATBCEnemyBase>> TempArray= PartySubclass->Enemies[0].EnemiesArray;
//	for (int8 i = 0; i < TempArray.Num(); ++i) {
//		UE_LOG(LogTemp, Log, TEXT("  EnemiesArray[%d] = %s"), i, *TempArray[i]->GetName());
//	}
//	TArray<ATBCEnemyBase*> ReturnArray;
//	for (TSubclassOf<ATBCEnemyBase>Character:TempArray)
//	{
//		ReturnArray.Add(Cast<ATBCEnemyBase>(Character));
//	}
//	return ReturnArray;
//}


