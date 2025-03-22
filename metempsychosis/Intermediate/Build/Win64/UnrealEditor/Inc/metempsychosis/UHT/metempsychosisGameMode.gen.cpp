// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "metempsychosis/metempsychosisGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodemetempsychosisGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
METEMPSYCHOSIS_API UClass* Z_Construct_UClass_AmetempsychosisGameMode();
METEMPSYCHOSIS_API UClass* Z_Construct_UClass_AmetempsychosisGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_metempsychosis();
// End Cross Module References

// Begin Class AmetempsychosisGameMode
void AmetempsychosisGameMode::StaticRegisterNativesAmetempsychosisGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AmetempsychosisGameMode);
UClass* Z_Construct_UClass_AmetempsychosisGameMode_NoRegister()
{
	return AmetempsychosisGameMode::StaticClass();
}
struct Z_Construct_UClass_AmetempsychosisGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "metempsychosisGameMode.h" },
		{ "ModuleRelativePath", "metempsychosisGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AmetempsychosisGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AmetempsychosisGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_metempsychosis,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AmetempsychosisGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AmetempsychosisGameMode_Statics::ClassParams = {
	&AmetempsychosisGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AmetempsychosisGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AmetempsychosisGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AmetempsychosisGameMode()
{
	if (!Z_Registration_Info_UClass_AmetempsychosisGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AmetempsychosisGameMode.OuterSingleton, Z_Construct_UClass_AmetempsychosisGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AmetempsychosisGameMode.OuterSingleton;
}
template<> METEMPSYCHOSIS_API UClass* StaticClass<AmetempsychosisGameMode>()
{
	return AmetempsychosisGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AmetempsychosisGameMode);
AmetempsychosisGameMode::~AmetempsychosisGameMode() {}
// End Class AmetempsychosisGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_metempsychosis_Source_metempsychosis_metempsychosisGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AmetempsychosisGameMode, AmetempsychosisGameMode::StaticClass, TEXT("AmetempsychosisGameMode"), &Z_Registration_Info_UClass_AmetempsychosisGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AmetempsychosisGameMode), 2746661392U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_metempsychosis_Source_metempsychosis_metempsychosisGameMode_h_312384593(TEXT("/Script/metempsychosis"),
	Z_CompiledInDeferFile_FID_metempsychosis_Source_metempsychosis_metempsychosisGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_metempsychosis_Source_metempsychosis_metempsychosisGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
