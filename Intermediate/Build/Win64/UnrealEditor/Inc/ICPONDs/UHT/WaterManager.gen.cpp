// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ICPONDs/WaterManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeWaterManager() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ICPONDS_API UClass* Z_Construct_UClass_AWaterManager();
ICPONDS_API UClass* Z_Construct_UClass_AWaterManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_ICPONDs();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AWaterManager Function GetWaterHeightAtLocation **************************
struct Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics
{
	struct WaterManager_eventGetWaterHeightAtLocation_Parms
	{
		FVector Location;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Water" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Get water height at specific location (including waves)\n" },
#endif
		{ "ModuleRelativePath", "WaterManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get water height at specific location (including waves)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(WaterManager_eventGetWaterHeightAtLocation_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Location_MetaData), NewProp_Location_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(WaterManager_eventGetWaterHeightAtLocation_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::NewProp_Location,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AWaterManager, nullptr, "GetWaterHeightAtLocation", Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::PropPointers), sizeof(Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::WaterManager_eventGetWaterHeightAtLocation_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::Function_MetaDataParams), Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::WaterManager_eventGetWaterHeightAtLocation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AWaterManager::execGetWaterHeightAtLocation)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Location);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetWaterHeightAtLocation(Z_Param_Out_Location);
	P_NATIVE_END;
}
// ********** End Class AWaterManager Function GetWaterHeightAtLocation ****************************

// ********** Begin Class AWaterManager Function IsLocationUnderwater ******************************
struct Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics
{
	struct WaterManager_eventIsLocationUnderwater_Parms
	{
		FVector Location;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Water" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Check if a location is underwater\n" },
#endif
		{ "ModuleRelativePath", "WaterManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Check if a location is underwater" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(WaterManager_eventIsLocationUnderwater_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Location_MetaData), NewProp_Location_MetaData) };
void Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((WaterManager_eventIsLocationUnderwater_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(WaterManager_eventIsLocationUnderwater_Parms), &Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::NewProp_Location,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AWaterManager, nullptr, "IsLocationUnderwater", Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::PropPointers), sizeof(Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::WaterManager_eventIsLocationUnderwater_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::Function_MetaDataParams), Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::WaterManager_eventIsLocationUnderwater_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AWaterManager_IsLocationUnderwater()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AWaterManager_IsLocationUnderwater_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AWaterManager::execIsLocationUnderwater)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Location);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsLocationUnderwater(Z_Param_Out_Location);
	P_NATIVE_END;
}
// ********** End Class AWaterManager Function IsLocationUnderwater ********************************

// ********** Begin Class AWaterManager ************************************************************
void AWaterManager::StaticRegisterNativesAWaterManager()
{
	UClass* Class = AWaterManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetWaterHeightAtLocation", &AWaterManager::execGetWaterHeightAtLocation },
		{ "IsLocationUnderwater", &AWaterManager::execIsLocationUnderwater },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AWaterManager;
UClass* AWaterManager::GetPrivateStaticClass()
{
	using TClass = AWaterManager;
	if (!Z_Registration_Info_UClass_AWaterManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("WaterManager"),
			Z_Registration_Info_UClass_AWaterManager.InnerSingleton,
			StaticRegisterNativesAWaterManager,
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
	return Z_Registration_Info_UClass_AWaterManager.InnerSingleton;
}
UClass* Z_Construct_UClass_AWaterManager_NoRegister()
{
	return AWaterManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AWaterManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "WaterManager.h" },
		{ "ModuleRelativePath", "WaterManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaterLevel_MetaData[] = {
		{ "Category", "Water" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Water properties\n" },
#endif
		{ "ModuleRelativePath", "WaterManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Water properties" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaveAmplitude_MetaData[] = {
		{ "Category", "Water" },
		{ "ModuleRelativePath", "WaterManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaveFrequency_MetaData[] = {
		{ "Category", "Water" },
		{ "ModuleRelativePath", "WaterManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaveSpeed_MetaData[] = {
		{ "Category", "Water" },
		{ "ModuleRelativePath", "WaterManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaterLevel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaveAmplitude;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaveFrequency;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaveSpeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AWaterManager_GetWaterHeightAtLocation, "GetWaterHeightAtLocation" }, // 2777037630
		{ &Z_Construct_UFunction_AWaterManager_IsLocationUnderwater, "IsLocationUnderwater" }, // 341750668
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWaterManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AWaterManager_Statics::NewProp_WaterLevel = { "WaterLevel", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWaterManager, WaterLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaterLevel_MetaData), NewProp_WaterLevel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AWaterManager_Statics::NewProp_WaveAmplitude = { "WaveAmplitude", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWaterManager, WaveAmplitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaveAmplitude_MetaData), NewProp_WaveAmplitude_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AWaterManager_Statics::NewProp_WaveFrequency = { "WaveFrequency", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWaterManager, WaveFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaveFrequency_MetaData), NewProp_WaveFrequency_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AWaterManager_Statics::NewProp_WaveSpeed = { "WaveSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWaterManager, WaveSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaveSpeed_MetaData), NewProp_WaveSpeed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWaterManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWaterManager_Statics::NewProp_WaterLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWaterManager_Statics::NewProp_WaveAmplitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWaterManager_Statics::NewProp_WaveFrequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWaterManager_Statics::NewProp_WaveSpeed,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWaterManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AWaterManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_ICPONDs,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWaterManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AWaterManager_Statics::ClassParams = {
	&AWaterManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AWaterManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AWaterManager_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWaterManager_Statics::Class_MetaDataParams), Z_Construct_UClass_AWaterManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AWaterManager()
{
	if (!Z_Registration_Info_UClass_AWaterManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWaterManager.OuterSingleton, Z_Construct_UClass_AWaterManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AWaterManager.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AWaterManager);
AWaterManager::~AWaterManager() {}
// ********** End Class AWaterManager **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h__Script_ICPONDs_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AWaterManager, AWaterManager::StaticClass, TEXT("AWaterManager"), &Z_Registration_Info_UClass_AWaterManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWaterManager), 3208306349U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h__Script_ICPONDs_3671000550(TEXT("/Script/ICPONDs"),
	Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h__Script_ICPONDs_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h__Script_ICPONDs_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
