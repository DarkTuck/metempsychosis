// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerParty.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "metempsychosisCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AmetempsychosisCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AmetempsychosisCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerParty)
	TSoftObjectPtr<UPlayerParty> PartyData;
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:

	virtual void NotifyControllerChanged() override;
	virtual void BeginPlay() override;
	//UPROPERTY()
	//TArray<ATBCPartyBase*> Parties;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 2) Po załadowaniu cache’ujemy wskaźnik, żeby Garbage Collector
	//    nie usunął obiektu i żeby nie wołać LoadSynchronous() za każdym razem.
	//UPROPERTY()
	//UPlayerParty* CachedPlayerParty;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	//UPROPERTY()
	//UPlayerParty* PartyDataAsset;
	//
	// // -----------------------
	// // 3) Funkcja zwracająca tablicę ATBCPartyBase*; jeśli asset jeszcze nie jest w pamięci,
	// //    spróbuje wczytać synchronously (jeżeli CachedPlayerParty == nullptr), a w razie niepowodzenia
	// //    zwróci pustą tablicę.
	// UFUNCTION(BlueprintCallable, Category = "Party")
	// TArray<ATBCPartyBase*> GetParties() const;
	//
	// // -----------------------
	// // 4) (Opcjonalnie) jeżeli chcesz ładować asynchronicznie przy starcie gry:
	// UFUNCTION(BlueprintCallable, Category = "Party")
	// void LoadPartyDataAsync();
	TArray<ATBCPartyBase*> GetParties() const;
private:
	class UAIPerceptionStimuliSourceComponent* StimulusSourceComponent;
	void SetupStimulusSource();
    void OnPartyDataLoaded();
};

