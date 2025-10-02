// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ICPONDs/FishingBobber.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeFishingBobber() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ICPONDS_API UClass* Z_Construct_UClass_AFishingBobber();
ICPONDS_API UClass* Z_Construct_UClass_AFishingBobber_NoRegister();
UPackage* Z_Construct_UPackage__Script_ICPONDs();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AFishingBobber ***********************************************************
void AFishingBobber::StaticRegisterNativesAFishingBobber()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AFishingBobber;
UClass* AFishingBobber::GetPrivateStaticClass()
{
	using TClass = AFishingBobber;
	if (!Z_Registration_Info_UClass_AFishingBobber.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("FishingBobber"),
			Z_Registration_Info_UClass_AFishingBobber.InnerSingleton,
			StaticRegisterNativesAFishingBobber,
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
	return Z_Registration_Info_UClass_AFishingBobber.InnerSingleton;
}
UClass* Z_Construct_UClass_AFishingBobber_NoRegister()
{
	return AFishingBobber::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AFishingBobber_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "FishingBobber.h" },
		{ "ModuleRelativePath", "FishingBobber.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sphere_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "FishingBobber.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BuoyancyStrength_MetaData[] = {
		{ "Category", "Bobber" },
		{ "ModuleRelativePath", "FishingBobber.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LinearDrag_MetaData[] = {
		{ "Category", "Bobber" },
		{ "ModuleRelativePath", "FishingBobber.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BobbingAmplitude_MetaData[] = {
		{ "Category", "Bobber" },
		{ "ModuleRelativePath", "FishingBobber.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BobbingFrequency_MetaData[] = {
		{ "Category", "Bobber" },
		{ "ModuleRelativePath", "FishingBobber.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Sphere;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BuoyancyStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LinearDrag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BobbingAmplitude;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BobbingFrequency;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFishingBobber>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFishingBobber_Statics::NewProp_Sphere = { "Sphere", nullptr, (EPropertyFlags)0x00400000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFishingBobber, Sphere), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sphere_MetaData), NewProp_Sphere_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFishingBobber_Statics::NewProp_BuoyancyStrength = { "BuoyancyStrength", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFishingBobber, BuoyancyStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BuoyancyStrength_MetaData), NewProp_BuoyancyStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFishingBobber_Statics::NewProp_LinearDrag = { "LinearDrag", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFishingBobber, LinearDrag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LinearDrag_MetaData), NewProp_LinearDrag_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFishingBobber_Statics::NewProp_BobbingAmplitude = { "BobbingAmplitude", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFishingBobber, BobbingAmplitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BobbingAmplitude_MetaData), NewProp_BobbingAmplitude_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFishingBobber_Statics::NewProp_BobbingFrequency = { "BobbingFrequency", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFishingBobber, BobbingFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BobbingFrequency_MetaData), NewProp_BobbingFrequency_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFishingBobber_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFishingBobber_Statics::NewProp_Sphere,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFishingBobber_Statics::NewProp_BuoyancyStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFishingBobber_Statics::NewProp_LinearDrag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFishingBobber_Statics::NewProp_BobbingAmplitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFishingBobber_Statics::NewProp_BobbingFrequency,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFishingBobber_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AFishingBobber_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_ICPONDs,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFishingBobber_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AFishingBobber_Statics::ClassParams = {
	&AFishingBobber::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AFishingBobber_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AFishingBobber_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AFishingBobber_Statics::Class_MetaDataParams), Z_Construct_UClass_AFishingBobber_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AFishingBobber()
{
	if (!Z_Registration_Info_UClass_AFishingBobber.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFishingBobber.OuterSingleton, Z_Construct_UClass_AFishingBobber_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AFishingBobber.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AFishingBobber);
AFishingBobber::~AFishingBobber() {}
// ********** End Class AFishingBobber *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_FishingBobber_h__Script_ICPONDs_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AFishingBobber, AFishingBobber::StaticClass, TEXT("AFishingBobber"), &Z_Registration_Info_UClass_AFishingBobber, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFishingBobber), 2239376176U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_FishingBobber_h__Script_ICPONDs_1951716374(TEXT("/Script/ICPONDs"),
	Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_FishingBobber_h__Script_ICPONDs_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_FishingBobber_h__Script_ICPONDs_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
