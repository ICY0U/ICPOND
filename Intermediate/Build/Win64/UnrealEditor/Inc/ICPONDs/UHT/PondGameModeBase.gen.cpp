// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ICPONDs/PondGameModeBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePondGameModeBase() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
ICPONDS_API UClass* Z_Construct_UClass_APondGameModeBase();
ICPONDS_API UClass* Z_Construct_UClass_APondGameModeBase_NoRegister();
UPackage* Z_Construct_UPackage__Script_ICPONDs();
// ********** End Cross Module References **********************************************************

// ********** Begin Class APondGameModeBase ********************************************************
void APondGameModeBase::StaticRegisterNativesAPondGameModeBase()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_APondGameModeBase;
UClass* APondGameModeBase::GetPrivateStaticClass()
{
	using TClass = APondGameModeBase;
	if (!Z_Registration_Info_UClass_APondGameModeBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PondGameModeBase"),
			Z_Registration_Info_UClass_APondGameModeBase.InnerSingleton,
			StaticRegisterNativesAPondGameModeBase,
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
	return Z_Registration_Info_UClass_APondGameModeBase.InnerSingleton;
}
UClass* Z_Construct_UClass_APondGameModeBase_NoRegister()
{
	return APondGameModeBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APondGameModeBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "PondGameModeBase.h" },
		{ "ModuleRelativePath", "PondGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APondGameModeBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_APondGameModeBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_ICPONDs,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APondGameModeBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APondGameModeBase_Statics::ClassParams = {
	&APondGameModeBase::StaticClass,
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
	0x009003ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APondGameModeBase_Statics::Class_MetaDataParams), Z_Construct_UClass_APondGameModeBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APondGameModeBase()
{
	if (!Z_Registration_Info_UClass_APondGameModeBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APondGameModeBase.OuterSingleton, Z_Construct_UClass_APondGameModeBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APondGameModeBase.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APondGameModeBase);
APondGameModeBase::~APondGameModeBase() {}
// ********** End Class APondGameModeBase **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_PondGameModeBase_h__Script_ICPONDs_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APondGameModeBase, APondGameModeBase::StaticClass, TEXT("APondGameModeBase"), &Z_Registration_Info_UClass_APondGameModeBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APondGameModeBase), 2616956048U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_PondGameModeBase_h__Script_ICPONDs_1885307338(TEXT("/Script/ICPONDs"),
	Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_PondGameModeBase_h__Script_ICPONDs_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_PondGameModeBase_h__Script_ICPONDs_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
