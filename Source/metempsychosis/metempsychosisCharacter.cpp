// Copyright Epic Games, Inc. All Rights Reserved.

#include "metempsychosisCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/AssetManager.h" 
#include "Engine/StreamableManager.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AmetempsychosisCharacter

AmetempsychosisCharacter::AmetempsychosisCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	SetupStimulusSource();
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AmetempsychosisCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AmetempsychosisCharacter::BeginPlay()
{
	Super::BeginPlay();
	//PartyDataAsset=NewObject<UPlayerParty>(this,PartyData);
	//TArray<ATBCPartyBase*> Parties=GetParties();
}

void AmetempsychosisCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AmetempsychosisCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AmetempsychosisCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

//TArray<ATBCPartyBase*> AmetempsychosisCharacter::GetParties() const
//{
//	UPlayerParty* const Parties= PartyData.LoadSynchronous();
//	return Parties->GetParties();
//}

// TArray<ATBCPartyBase*> AmetempsychosisCharacter::GetParties() const
// {
// 	// Jeżeli już mamy CachedPlayerParty, to od razu zwróćmy z niej tablicę
// 	if (CachedPlayerParty)
// 	{
// 		return CachedPlayerParty->GetParties();
// 	}
//
// 	// Jeżeli nie ma w cache, spróbujemy załadować synchronically (może to zablokować framę przez chwilę)
// 	// 1) Sprawdźmy najpierw, czy SoftObjectPath jest w ogóle poprawny:
// 	if (!PartyData.ToSoftObjectPath().IsValid())
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("GetParties: PartyData ma pustą / niepoprawną ścieżkę."));
// 		return TArray<ATBCPartyBase*>();
// 	}
//
// 	// 2) Wywołujemy LoadSynchronous() – zwróci nullptr, jeżeli asset wygasł lub nie istnieje
// 	UPlayerParty* LoadedParty = PartyData.LoadSynchronous();
// 	if (!LoadedParty)
// 	{
// 		UE_LOG(LogTemp, Error, TEXT(
// 			"GetParties: LoadSynchronous() zwróciło nullptr dla %s"),
// 			*PartyData.ToSoftObjectPath().ToString()
// 		);
// 		return TArray<ATBCPartyBase*>();
// 	}
//
// 	// 3) Jeżeli udało się załadować, przechowajmy w cache (żeby następnym razem nie wywoływać ponownie sync-load)
// 	//    Uwaga: musimy rzucić const-cast, ponieważ CachedPlayerParty nie jest const
// 	AmetempsychosisCharacter* MutableThis = const_cast<AmetempsychosisCharacter*>(this);
// 	MutableThis->CachedPlayerParty = LoadedParty;
//
// 	// 4) I wreszcie zwracamy wynik
// 	return LoadedParty->GetParties();
// }

// TArray<ATBCPartyBase*> AmetempsychosisCharacter::GetParties() const
// {
//     if (CachedPlayerParty)
//     {
//         return CachedPlayerParty->GetParties();
//     }
//
//     // Spróbujmy wczytać synchronously, jeżeli asset jeszcze nie jest w pamięci
//     if (PartyData.ToSoftObjectPath().IsValid())
//     {
//         UPlayerParty* Loaded = PartyData.LoadSynchronous();
//         if (Loaded)
//         {
//             // const_cast, bo chcemy w cache’ować w wersji niestałej
//             const_cast<AmetempsychosisCharacter*>(this)->CachedPlayerParty = Loaded;
//             return Loaded->GetParties();
//         }
//     }
//
//     // Jeżeli nie wyszło, zwróć pustą
//     return {};
// }

// void AmetempsychosisCharacter::LoadPartyDataAsync()
// {
// 	// 1) Sprawdźmy, czy jest „ścieżka” w PartyData
// 	const FSoftObjectPath AssetPath = PartyData.ToSoftObjectPath();
// 	if (!AssetPath.IsValid())
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("LoadPartyDataAsync: PartyData path niepoprawny lub pusty."));
// 		return;
// 	}
//
// 	UE_LOG(LogTemp, Warning, TEXT("LoadPartyDataAsync: Rozpoczynam asynchroniczne ładowanie: %s"),
// 		   *AssetPath.ToString());
//
// 	// 2) Pobieramy StreamableManager z AssetManagera
// 	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
//
// 	// 3) Rejestrujemy delegata, który wywoła się po zakończeniu ładowania
// 	FStreamableDelegate LoadDelegate = FStreamableDelegate::CreateUObject(
// 		this,
// 		&AmetempsychosisCharacter::OnPartyDataLoaded
// 	);
//
// 	// 4) RequestAsyncLoad – trzeci parametr to priorytet (tu: High)
// 	Streamable.RequestAsyncLoad(AssetPath, LoadDelegate, FStreamableManager::AsyncLoadHighPriority);
// }
//
// void AmetempsychosisCharacter::OnPartyDataLoaded()
// {
// 	// 1) Po zakończeniu asynchronicznego ładowania możemy pobrać już wskaźnik:
// 	UPlayerParty* LoadedParty = PartyData.Get();
// 	if (!LoadedParty)
// 	{
// 		UE_LOG(LogTemp, Error, TEXT(
// 			"OnPartyDataLoaded: nie udało się pobrać UPlayerParty z PartyData"));
// 		return;
// 	}
//
// 	// 2) Zapiszmy w cache
// 	CachedPlayerParty = LoadedParty;
//
// 	// 3) Logujemy sukces
// 	UE_LOG(LogTemp, Log, TEXT("OnPartyDataLoaded: PartyData załadowane poprawnie: %s"),
// 		   *PartyData.ToSoftObjectPath().ToString()
// 	);
//
// 	// 4) Teraz, jeśli ktoś od razu chciałby wywołać GetParties(), będzie od razu w cache
// 	//    (możesz też tu wypisać wynik na log, jeśli chcesz)
// 	TArray<ATBCPartyBase*> PartiesArray = CachedPlayerParty->GetParties();
// 	UE_LOG(LogTemp, Warning, TEXT("OnPartyDataLoaded: GetParties() zwróciło %d elementów."),
// 		   PartiesArray.Num());
// }


TArray<ATBCPartyBase*> AmetempsychosisCharacter::GetParties() const
{
	return PartyData.LoadSynchronous()->GetParties();
}

void AmetempsychosisCharacter::SetupStimulusSource()
{
	StimulusSourceComponent= CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimulusSource"));
	if (StimulusSourceComponent)
	{
		StimulusSourceComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSourceComponent->RegisterWithPerceptionSystem();
	}
}

void AmetempsychosisCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AmetempsychosisCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
