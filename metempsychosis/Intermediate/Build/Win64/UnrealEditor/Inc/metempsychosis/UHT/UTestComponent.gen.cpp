// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "metempsychosis/Public/UTestComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUTestComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
METEMPSYCHOSIS_API UClass* Z_Construct_UClass_UUTestComponent();
METEMPSYCHOSIS_API UClass* Z_Construct_UClass_UUTestComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_metempsychosis();
// End Cross Module References

// Begin Class UUTestComponent
void UUTestComponent::StaticRegisterNativesUUTestComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UUTestComponent);
UClass* Z_Construct_UClass_UUTestComponent_NoRegister()
{
	return UUTestComponent::StaticClass();
}
struct Z_Construct_UClass_UUTestComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "UTestComponent.h" },
		{ "ModuleRelativePath", "Public/UTestComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UUTestComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UUTestComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_metempsychosis,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UUTestComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UUTestComponent_Statics::ClassParams = {
	&UUTestComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UUTestComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UUTestComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UUTestComponent()
{
	if (!Z_Registration_Info_UClass_UUTestComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UUTestComponent.OuterSingleton, Z_Construct_UClass_UUTestComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UUTestComponent.OuterSingleton;
}
template<> METEMPSYCHOSIS_API UClass* StaticClass<UUTestComponent>()
{
	return UUTestComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UUTestComponent);
UUTestComponent::~UUTestComponent() {}
// End Class UUTestComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_metempsychosis_Source_metempsychosis_Public_UTestComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UUTestComponent, UUTestComponent::StaticClass, TEXT("UUTestComponent"), &Z_Registration_Info_UClass_UUTestComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UUTestComponent), 4064815906U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_metempsychosis_Source_metempsychosis_Public_UTestComponent_h_200854915(TEXT("/Script/metempsychosis"),
	Z_CompiledInDeferFile_FID_metempsychosis_Source_metempsychosis_Public_UTestComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_metempsychosis_Source_metempsychosis_Public_UTestComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
