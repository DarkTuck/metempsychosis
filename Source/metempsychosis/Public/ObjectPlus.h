// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ObjectPlus.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class METEMPSYCHOSIS_API UObjectPlus : public UObject
{
	GENERATED_BODY()

public:
	UObjectPlus();
	virtual ~UObjectPlus() override;

	// Stałe
	static const FString EXTENT_NAME;

	// Statyczne metody do zapisywania/wczytywania extentu
	UFUNCTION(BlueprintCallable, Category = "ObjectPlus")
	static void SaveExtent();

	UFUNCTION(BlueprintCallable, Category = "ObjectPlus")
	static void LoadExtent();

	/** Ręczna rejestracja dowolnego UObject w extent (nawet jeśli nie dziedziczy po UObjectPlus). */
	UFUNCTION(BlueprintCallable, Category = "ObjectPlus|Extent")
	static void RegisterObject(UObject* Obj);

	/** Ręczne usunięcie dowolnego UObject z extent. */
	UFUNCTION(BlueprintCallable, Category = "ObjectPlus|Extent")
	static void UnregisterObject(UObject* Obj);


	// Metoda do pobierania wszystkich obiektów danego typu
	template<typename T>
	static TArray<T*> GetExtentFromClass()
	{
		TArray<T*> Result;
		UClass* Class = T::StaticClass();
        
		if (!GetExtent().Contains(Class))
		{
			GetExtent().Add(Class, TArray<UObject*>());
		}
        
		const TArray<UObject*>& ClassExtent = GetExtent()[Class];
		for (UObject* Obj : ClassExtent)
		{
			if (T* TypedObj = Cast<T>(Obj))
			{
				Result.Add(TypedObj);
			}
		}
        
		return Result;
	}

	// Blueprint-dostępna wersja GetExtentFromClass
	UFUNCTION(BlueprintCallable, Category = "ObjectPlus")
	static TArray<UObject*> GetExtentFromClassBP(UClass* Class);

protected:
	void AddToExtent();
	void RemoveFromExtent();

private:
	// Statyczna mapa przechowująca extent
	static TMap<UClass*, TArray<UObject*>>& GetExtent()
	{
		static TMap<UClass*, TArray<UObject*>> ExtentInstance;
		return ExtentInstance;
	}
};
