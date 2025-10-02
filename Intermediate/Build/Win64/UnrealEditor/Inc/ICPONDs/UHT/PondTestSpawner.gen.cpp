// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ICPONDs/PondTestSpawner.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePondTestSpawner() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ICPONDS_API UClass* Z_Construct_UClass_APondTestSpawner();
ICPONDS_API UClass* Z_Construct_UClass_APondTestSpawner_NoRegister();
UPackage* Z_Construct_UPackage__Script_ICPONDs();
// ********** End Cross Module References **********************************************************

// ********** Begin Class APondTestSpawner *********************************************************
void APondTestSpawner::StaticRegisterNativesAPondTestSpawner()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_APondTestSpawner;
UClass* APondTestSpawner::GetPrivateStaticClass()
{
	using TClass = APondTestSpawner;
	if (!Z_Registration_Info_UClass_APondTestSpawner.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PondTestSpawner"),
			Z_Registration_Info_UClass_APondTestSpawner.InnerSingleton,
			StaticRegisterNativesAPondTestSpawner,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_APondTestSpawner.InnerSingleton;
}
UClass* Z_Construct_UClass_APondTestSpawner_NoRegister()
{
	return APondTestSpawner::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APondTestSpawner_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "PondTestSpawner.h" },
		{ "ModuleRelativePath", "PondTestSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PondRadius_MetaData[] = {
		{ "Category", "Pond" },
		{ "ModuleRelativePath", "PondTestSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IslandRingRadius_MetaData[] = {
		{ "Category", "Pond" },
		{ "ModuleRelativePath", "PondTestSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumIslands_MetaData[] = {
		{ "Category", "Pond" },
		{ "ModuleRelativePath", "PondTestSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentStrength_MetaData[] = {
		{ "Category", "Pond" },
		{ "ModuleRelativePath", "PondTestSpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentRingHeight_MetaData[] = {
		{ "Category", "Pond" },
		{ "ModuleRelativePath", "PondTestSpawner.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PondRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_IslandRingRadius;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumIslands;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentRingHeight;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APondTestSpawner>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APondTestSpawner_Statics::NewProp_PondRadius = { "PondRadius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APondTestSpawner, PondRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PondRadius_MetaData), NewProp_PondRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APondTestSpawner_Statics::NewProp_IslandRingRadius = { "IslandRingRadius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APondTestSpawner, IslandRingRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IslandRingRadius_MetaData), NewProp_IslandRingRadius_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_APondTestSpawner_Statics::NewProp_NumIslands = { "NumIslands", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APondTestSpawner, NumIslands), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumIslands_MetaData), NewProp_NumIslands_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APondTestSpawner_Statics::NewProp_CurrentStrength = { "CurrentStrength", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APondTestSpawner, CurrentStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentStrength_MetaData), NewProp_CurrentStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APondTestSpawner_Statics::NewProp_CurrentRingHeight = { "CurrentRingHeight", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APondTestSpawner, CurrentRingHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentRingHeight_MetaData), NewProp_CurrentRingHeight_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APondTestSpawner_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APondTestSpawner_Statics::NewProp_PondRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APondTestSpawner_Statics::NewProp_IslandRingRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APondTestSpawner_Statics::NewProp_NumIslands,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APondTestSpawner_Statics::NewProp_CurrentStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APondTestSpawner_Statics::NewProp_CurrentRingHeight,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APondTestSpawner_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APondTestSpawner_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_ICPONDs,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APondTestSpawner_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APondTestSpawner_Statics::ClassParams = {
	&APondTestSpawner::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_APondTestSpawner_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_APondTestSpawner_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APondTestSpawner_Statics::Class_MetaDataParams), Z_Construct_UClass_APondTestSpawner_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APondTestSpawner()
{
	if (!Z_Registration_Info_UClass_APondTestSpawner.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APondTestSpawner.OuterSingleton, Z_Construct_UClass_APondTestSpawner_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APondTestSpawner.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APondTestSpawner);
APondTestSpawner::~APondTestSpawner() {}
// ********** End Class APondTestSpawner ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_PondTestSpawner_h__Script_ICPONDs_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APondTestSpawner, APondTestSpawner::StaticClass, TEXT("APondTestSpawner"), &Z_Registration_Info_UClass_APondTestSpawner, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APondTestSpawner), 2956214098U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_PondTestSpawner_h__Script_ICPONDs_1882573937(TEXT("/Script/ICPONDs"),
	Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_PondTestSpawner_h__Script_ICPONDs_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_PondTestSpawner_h__Script_ICPONDs_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
