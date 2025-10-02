// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ICPONDs/CurrentVolume.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeCurrentVolume() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
ICPONDS_API UClass* Z_Construct_UClass_ACurrentVolume();
ICPONDS_API UClass* Z_Construct_UClass_ACurrentVolume_NoRegister();
UPackage* Z_Construct_UPackage__Script_ICPONDs();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ACurrentVolume ***********************************************************
void ACurrentVolume::StaticRegisterNativesACurrentVolume()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACurrentVolume;
UClass* ACurrentVolume::GetPrivateStaticClass()
{
	using TClass = ACurrentVolume;
	if (!Z_Registration_Info_UClass_ACurrentVolume.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("CurrentVolume"),
			Z_Registration_Info_UClass_ACurrentVolume.InnerSingleton,
			StaticRegisterNativesACurrentVolume,
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
	return Z_Registration_Info_UClass_ACurrentVolume.InnerSingleton;
}
UClass* Z_Construct_UClass_ACurrentVolume_NoRegister()
{
	return ACurrentVolume::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ACurrentVolume_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "CurrentVolume.h" },
		{ "ModuleRelativePath", "CurrentVolume.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Box_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "CurrentVolume.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FlowDirection_MetaData[] = {
		{ "Category", "Current" },
		{ "ModuleRelativePath", "CurrentVolume.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FlowStrength_MetaData[] = {
		{ "Category", "Current" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "CurrentVolume.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAffectNonPhysicsPawns_MetaData[] = {
		{ "Category", "Current" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// approximate newtons\n" },
#endif
		{ "ModuleRelativePath", "CurrentVolume.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "approximate newtons" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Box;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FlowDirection;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FlowStrength;
	static void NewProp_bAffectNonPhysicsPawns_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAffectNonPhysicsPawns;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACurrentVolume>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ACurrentVolume_Statics::NewProp_Box = { "Box", nullptr, (EPropertyFlags)0x00400000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACurrentVolume, Box), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Box_MetaData), NewProp_Box_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ACurrentVolume_Statics::NewProp_FlowDirection = { "FlowDirection", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACurrentVolume, FlowDirection), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FlowDirection_MetaData), NewProp_FlowDirection_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ACurrentVolume_Statics::NewProp_FlowStrength = { "FlowStrength", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACurrentVolume, FlowStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FlowStrength_MetaData), NewProp_FlowStrength_MetaData) };
void Z_Construct_UClass_ACurrentVolume_Statics::NewProp_bAffectNonPhysicsPawns_SetBit(void* Obj)
{
	((ACurrentVolume*)Obj)->bAffectNonPhysicsPawns = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ACurrentVolume_Statics::NewProp_bAffectNonPhysicsPawns = { "bAffectNonPhysicsPawns", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ACurrentVolume), &Z_Construct_UClass_ACurrentVolume_Statics::NewProp_bAffectNonPhysicsPawns_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAffectNonPhysicsPawns_MetaData), NewProp_bAffectNonPhysicsPawns_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACurrentVolume_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACurrentVolume_Statics::NewProp_Box,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACurrentVolume_Statics::NewProp_FlowDirection,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACurrentVolume_Statics::NewProp_FlowStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACurrentVolume_Statics::NewProp_bAffectNonPhysicsPawns,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACurrentVolume_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ACurrentVolume_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_ICPONDs,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACurrentVolume_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ACurrentVolume_Statics::ClassParams = {
	&ACurrentVolume::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ACurrentVolume_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ACurrentVolume_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACurrentVolume_Statics::Class_MetaDataParams), Z_Construct_UClass_ACurrentVolume_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ACurrentVolume()
{
	if (!Z_Registration_Info_UClass_ACurrentVolume.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACurrentVolume.OuterSingleton, Z_Construct_UClass_ACurrentVolume_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ACurrentVolume.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ACurrentVolume);
ACurrentVolume::~ACurrentVolume() {}
// ********** End Class ACurrentVolume *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_CurrentVolume_h__Script_ICPONDs_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACurrentVolume, ACurrentVolume::StaticClass, TEXT("ACurrentVolume"), &Z_Registration_Info_UClass_ACurrentVolume, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACurrentVolume), 2894656349U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_CurrentVolume_h__Script_ICPONDs_1731962604(TEXT("/Script/ICPONDs"),
	Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_CurrentVolume_h__Script_ICPONDs_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_CurrentVolume_h__Script_ICPONDs_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
