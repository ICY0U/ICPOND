// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ICPONDs/SimpleWaterPlane.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSimpleWaterPlane() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ICPONDS_API UClass* Z_Construct_UClass_ASimpleWaterPlane();
ICPONDS_API UClass* Z_Construct_UClass_ASimpleWaterPlane_NoRegister();
UPackage* Z_Construct_UPackage__Script_ICPONDs();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASimpleWaterPlane ********************************************************
void ASimpleWaterPlane::StaticRegisterNativesASimpleWaterPlane()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASimpleWaterPlane;
UClass* ASimpleWaterPlane::GetPrivateStaticClass()
{
	using TClass = ASimpleWaterPlane;
	if (!Z_Registration_Info_UClass_ASimpleWaterPlane.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SimpleWaterPlane"),
			Z_Registration_Info_UClass_ASimpleWaterPlane.InnerSingleton,
			StaticRegisterNativesASimpleWaterPlane,
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
	return Z_Registration_Info_UClass_ASimpleWaterPlane.InnerSingleton;
}
UClass* Z_Construct_UClass_ASimpleWaterPlane_NoRegister()
{
	return ASimpleWaterPlane::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASimpleWaterPlane_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "SimpleWaterPlane.h" },
		{ "ModuleRelativePath", "SimpleWaterPlane.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Plane_MetaData[] = {
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SimpleWaterPlane.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Plane;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASimpleWaterPlane>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASimpleWaterPlane_Statics::NewProp_Plane = { "Plane", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASimpleWaterPlane, Plane), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Plane_MetaData), NewProp_Plane_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASimpleWaterPlane_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASimpleWaterPlane_Statics::NewProp_Plane,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleWaterPlane_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASimpleWaterPlane_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_ICPONDs,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleWaterPlane_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASimpleWaterPlane_Statics::ClassParams = {
	&ASimpleWaterPlane::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASimpleWaterPlane_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleWaterPlane_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASimpleWaterPlane_Statics::Class_MetaDataParams), Z_Construct_UClass_ASimpleWaterPlane_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASimpleWaterPlane()
{
	if (!Z_Registration_Info_UClass_ASimpleWaterPlane.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASimpleWaterPlane.OuterSingleton, Z_Construct_UClass_ASimpleWaterPlane_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASimpleWaterPlane.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASimpleWaterPlane);
ASimpleWaterPlane::~ASimpleWaterPlane() {}
// ********** End Class ASimpleWaterPlane **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_SimpleWaterPlane_h__Script_ICPONDs_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASimpleWaterPlane, ASimpleWaterPlane::StaticClass, TEXT("ASimpleWaterPlane"), &Z_Registration_Info_UClass_ASimpleWaterPlane, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASimpleWaterPlane), 771892698U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_SimpleWaterPlane_h__Script_ICPONDs_1079721495(TEXT("/Script/ICPONDs"),
	Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_SimpleWaterPlane_h__Script_ICPONDs_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_SimpleWaterPlane_h__Script_ICPONDs_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
