#include "ObjectPlus.h"
#include "HAL/PlatformFilemanager.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/MemoryReader.h"
#include "Misc/FileHelper.h"

const FString UObjectPlus::EXTENT_NAME = TEXT("extent.sav");

UObjectPlus::UObjectPlus()
{
    AddToExtent();
}

UObjectPlus::~UObjectPlus()
{
    RemoveFromExtent();
}

void UObjectPlus::SaveExtent()
{
    FBufferArchive BinaryData;
    
    // Zapisz liczbę klas
    int32 ClassCount = GetExtent().Num();
    BinaryData << ClassCount;

    // Dla każdej klasy
    for (const auto& Pair : GetExtent())
    {
        // Zapisz nazwę klasy
        FString ClassName = Pair.Key->GetName();
        BinaryData << ClassName;

        // Zapisz obiekty
        const TArray<UObject*>& Objects = Pair.Value;
        int32 ObjectCount = Objects.Num();
        BinaryData << ObjectCount;

        for (const UObject* Obj : Objects)
        {
            if (Obj)
            {
                FString ObjectName = Obj->GetName();
                BinaryData << ObjectName;
            }
        }
    }

    // Zapisz do pliku
    if (FFileHelper::SaveArrayToFile(BinaryData, *EXTENT_NAME))
    {
        UE_LOG(LogTemp, Log, TEXT("Extent saved successfully"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to save extent"));
    }
}

void UObjectPlus::LoadExtent()
{
    // Wyczyść aktualny extent
    GetExtent().Empty();

    TArray<uint8> FileData;
    if (!FFileHelper::LoadFileToArray(FileData, *EXTENT_NAME))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load extent file"));
        return;
    }

    FMemoryReader MemoryReader(FileData, true);

    // Wczytaj liczbę klas
    int32 ClassCount;
    MemoryReader << ClassCount;

    // Dla każdej klasy
    for (int32 i = 0; i < ClassCount; ++i)
    {
        FString ClassName;
        MemoryReader << ClassName;

        // Znajdź klasę
        UClass* Class = FindObject<UClass>(ANY_PACKAGE, *ClassName);
        if (!Class)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to find class: %s"), *ClassName);
            continue;
        }

        // Wczytaj obiekty
        int32 ObjectCount;
        MemoryReader << ObjectCount;

        TArray<UObject*> Objects;
        for (int32 j = 0; j < ObjectCount; ++j)
        {
            FString ObjectName;
            MemoryReader << ObjectName;

            // Stwórz nowy obiekt
            if (UObject* CreatedObject = NewObject<UObject>(GetTransientPackage(), Class))
            {
                CreatedObject->Rename(*ObjectName);
                Objects.Add(CreatedObject);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create object of class %s with name %s"), *ClassName, *ObjectName);
            }

        }

        GetExtent().Add(Class, Objects);
    }

    UE_LOG(LogTemp, Log, TEXT("Extent loaded successfully"));
}

void UObjectPlus::RegisterObject(UObject* Obj)
{
    if (!Obj)
    {
        UE_LOG(LogTemp, Warning, TEXT("RegisterObject: przekazano nullptr"));
        return;
    }

    UClass* Class = Obj->GetClass();
    // Jeśli jeszcze nie ma takiego klucza w mapie, to dopisujemy nową pustą tablicę
    if (!GetExtent().Contains(Class))
    {
        GetExtent().Add(Class, TArray<UObject*>());
    }
    // Dodajemy obiekt do wewnętrznej listy
    GetExtent()[Class].Add(Obj);
}

void UObjectPlus::UnregisterObject(UObject* Obj)
{
    if (!Obj) return;

    UClass* Class = Obj->GetClass();
    if (TArray<UObject*>* Arr = GetExtent().Find(Class))
    {
        Arr->Remove(Obj);
    }
}

TArray<UObject*> UObjectPlus::GetExtentFromClassBP(UClass* Class)
{
    if (!GetExtent().Contains(Class))
    {
        GetExtent().Add(Class, TArray<UObject*>());
    }
    return GetExtent()[Class];
}

void UObjectPlus::AddToExtent()
{
    UClass* Class = GetClass();
    if (!GetExtent().Contains(Class))
    {
        GetExtent().Add(Class, TArray<UObject*>());
    }
    GetExtent()[Class].Add(this);
}

void UObjectPlus::RemoveFromExtent()
{
    const UClass* Class = GetClass();
    if (TArray<UObject*>* Objects = GetExtent().Find(Class))
    {
        Objects->Remove(this);
    }
}
