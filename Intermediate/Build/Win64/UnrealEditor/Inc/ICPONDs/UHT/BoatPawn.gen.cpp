// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ICPONDs/BoatPawn.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeBoatPawn() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APawn();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ICPONDS_API UClass* Z_Construct_UClass_ABoatPawn();
ICPONDS_API UClass* Z_Construct_UClass_ABoatPawn_NoRegister();
ICPONDS_API UClass* Z_Construct_UClass_AFishingBobber_NoRegister();
UPackage* Z_Construct_UPackage__Script_ICPONDs();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ABoatPawn Function ResetBoatPosition *************************************
struct Z_Construct_UFunction_ABoatPawn_ResetBoatPosition_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Boat|Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Emergency function to reset boat position above water\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Emergency function to reset boat position above water" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABoatPawn_ResetBoatPosition_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABoatPawn, nullptr, "ResetBoatPosition", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABoatPawn_ResetBoatPosition_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABoatPawn_ResetBoatPosition_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_ABoatPawn_ResetBoatPosition()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABoatPawn_ResetBoatPosition_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ABoatPawn::execResetBoatPosition)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetBoatPosition();
	P_NATIVE_END;
}
// ********** End Class ABoatPawn Function ResetBoatPosition ***************************************

// ********** Begin Class ABoatPawn Function SetWaterLevel *****************************************
struct Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics
{
	struct BoatPawn_eventSetWaterLevel_Parms
	{
		float NewWaterLevel;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Boat|Water" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Function to update water level from WaterManager\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Function to update water level from WaterManager" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewWaterLevel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::NewProp_NewWaterLevel = { "NewWaterLevel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BoatPawn_eventSetWaterLevel_Parms, NewWaterLevel), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::NewProp_NewWaterLevel,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ABoatPawn, nullptr, "SetWaterLevel", Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::PropPointers), sizeof(Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::BoatPawn_eventSetWaterLevel_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::Function_MetaDataParams), Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::BoatPawn_eventSetWaterLevel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ABoatPawn_SetWaterLevel()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ABoatPawn_SetWaterLevel_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ABoatPawn::execSetWaterLevel)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewWaterLevel);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetWaterLevel(Z_Param_NewWaterLevel);
	P_NATIVE_END;
}
// ********** End Class ABoatPawn Function SetWaterLevel *******************************************

// ********** Begin Class ABoatPawn ****************************************************************
void ABoatPawn::StaticRegisterNativesABoatPawn()
{
	UClass* Class = ABoatPawn::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ResetBoatPosition", &ABoatPawn::execResetBoatPosition },
		{ "SetWaterLevel", &ABoatPawn::execSetWaterLevel },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ABoatPawn;
UClass* ABoatPawn::GetPrivateStaticClass()
{
	using TClass = ABoatPawn;
	if (!Z_Registration_Info_UClass_ABoatPawn.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("BoatPawn"),
			Z_Registration_Info_UClass_ABoatPawn.InnerSingleton,
			StaticRegisterNativesABoatPawn,
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
	return Z_Registration_Info_UClass_ABoatPawn.InnerSingleton;
}
UClass* Z_Construct_UClass_ABoatPawn_NoRegister()
{
	return ABoatPawn::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ABoatPawn_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "BoatPawn.h" },
		{ "ModuleRelativePath", "BoatPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CastDistance_MetaData[] = {
		{ "Category", "Boat|Fishing" },
		{ "ModuleRelativePath", "BoatPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CastImpulse_MetaData[] = {
		{ "Category", "Boat|Fishing" },
		{ "ModuleRelativePath", "BoatPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveBobber_MetaData[] = {
		{ "ModuleRelativePath", "BoatPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoatMesh_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Boat Components\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Boat Components" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpringArm_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Your custom boat mesh\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Your custom boat mesh" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Camera boom for third-person view\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom for third-person view" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxThrust_MetaData[] = {
		{ "Category", "Boat|Movement" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Movement System Properties\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Movement System Properties" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TurnTorque_MetaData[] = {
		{ "Category", "Boat|Movement" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Forward/backward thrust force\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Forward/backward thrust force" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxSpeed_MetaData[] = {
		{ "Category", "Boat|Movement" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Turning force\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Turning force" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraShakeIntensity_MetaData[] = {
		{ "Category", "Boat|Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Camera System Properties\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera System Properties" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraFollowSpeed_MetaData[] = {
		{ "Category", "Boat|Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// How much camera shakes during movement\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How much camera shakes during movement" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouseSensitivityX_MetaData[] = {
		{ "Category", "Boat|Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// How smoothly camera follows boat movement\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How smoothly camera follows boat movement" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouseSensitivityY_MetaData[] = {
		{ "Category", "Boat|Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Horizontal mouse sensitivity\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Horizontal mouse sensitivity" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinPitchAngle_MetaData[] = {
		{ "Category", "Boat|Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Vertical mouse sensitivity\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Vertical mouse sensitivity" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxPitchAngle_MetaData[] = {
		{ "Category", "Boat|Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Maximum upward camera angle\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum upward camera angle" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableMouseControl_MetaData[] = {
		{ "Category", "Boat|Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Maximum downward camera angle\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum downward camera angle" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaterLevel_MetaData[] = {
		{ "Category", "Boat|Water Physics" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Enhanced Water Physics\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enhanced Water Physics" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BuoyancyForce_MetaData[] = {
		{ "Category", "Boat|Water Physics" },
		{ "ModuleRelativePath", "BoatPawn.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaterDensity_MetaData[] = {
		{ "Category", "Boat|Water Physics" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Increased for stronger floating\n" },
#endif
		{ "ModuleRelativePath", "BoatPawn.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Increased for stronger floating" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SubmersionDepth_MetaData[] = {
		{ "Category", "Boat|Water Physics" },
		{ "ModuleRelativePath", "BoatPawn.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CastDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CastImpulse;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActiveBobber;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BoatMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpringArm;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxThrust;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TurnTorque;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraShakeIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraFollowSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MouseSensitivityX;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MouseSensitivityY;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinPitchAngle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxPitchAngle;
	static void NewProp_bEnableMouseControl_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableMouseControl;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaterLevel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BuoyancyForce;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaterDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SubmersionDepth;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ABoatPawn_ResetBoatPosition, "ResetBoatPosition" }, // 1785945457
		{ &Z_Construct_UFunction_ABoatPawn_SetWaterLevel, "SetWaterLevel" }, // 2117394590
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ABoatPawn>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_CastDistance = { "CastDistance", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, CastDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CastDistance_MetaData), NewProp_CastDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_CastImpulse = { "CastImpulse", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, CastImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CastImpulse_MetaData), NewProp_CastImpulse_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_ActiveBobber = { "ActiveBobber", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, ActiveBobber), Z_Construct_UClass_AFishingBobber_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveBobber_MetaData), NewProp_ActiveBobber_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_BoatMesh = { "BoatMesh", nullptr, (EPropertyFlags)0x00400000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, BoatMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoatMesh_MetaData), NewProp_BoatMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_SpringArm = { "SpringArm", nullptr, (EPropertyFlags)0x00400000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, SpringArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpringArm_MetaData), NewProp_SpringArm_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x00400000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Camera_MetaData), NewProp_Camera_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_MaxThrust = { "MaxThrust", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, MaxThrust), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxThrust_MetaData), NewProp_MaxThrust_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_TurnTorque = { "TurnTorque", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, TurnTorque), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TurnTorque_MetaData), NewProp_TurnTorque_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_MaxSpeed = { "MaxSpeed", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, MaxSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxSpeed_MetaData), NewProp_MaxSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_CameraShakeIntensity = { "CameraShakeIntensity", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, CameraShakeIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraShakeIntensity_MetaData), NewProp_CameraShakeIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_CameraFollowSpeed = { "CameraFollowSpeed", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, CameraFollowSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraFollowSpeed_MetaData), NewProp_CameraFollowSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_MouseSensitivityX = { "MouseSensitivityX", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, MouseSensitivityX), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouseSensitivityX_MetaData), NewProp_MouseSensitivityX_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_MouseSensitivityY = { "MouseSensitivityY", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, MouseSensitivityY), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouseSensitivityY_MetaData), NewProp_MouseSensitivityY_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_MinPitchAngle = { "MinPitchAngle", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, MinPitchAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinPitchAngle_MetaData), NewProp_MinPitchAngle_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_MaxPitchAngle = { "MaxPitchAngle", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, MaxPitchAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxPitchAngle_MetaData), NewProp_MaxPitchAngle_MetaData) };
void Z_Construct_UClass_ABoatPawn_Statics::NewProp_bEnableMouseControl_SetBit(void* Obj)
{
	((ABoatPawn*)Obj)->bEnableMouseControl = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_bEnableMouseControl = { "bEnableMouseControl", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ABoatPawn), &Z_Construct_UClass_ABoatPawn_Statics::NewProp_bEnableMouseControl_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableMouseControl_MetaData), NewProp_bEnableMouseControl_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_WaterLevel = { "WaterLevel", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, WaterLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaterLevel_MetaData), NewProp_WaterLevel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_BuoyancyForce = { "BuoyancyForce", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, BuoyancyForce), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BuoyancyForce_MetaData), NewProp_BuoyancyForce_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_WaterDensity = { "WaterDensity", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, WaterDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaterDensity_MetaData), NewProp_WaterDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ABoatPawn_Statics::NewProp_SubmersionDepth = { "SubmersionDepth", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ABoatPawn, SubmersionDepth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SubmersionDepth_MetaData), NewProp_SubmersionDepth_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ABoatPawn_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_CastDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_CastImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_ActiveBobber,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_BoatMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_SpringArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_Camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_MaxThrust,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_TurnTorque,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_MaxSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_CameraShakeIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_CameraFollowSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_MouseSensitivityX,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_MouseSensitivityY,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_MinPitchAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_MaxPitchAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_bEnableMouseControl,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_WaterLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_BuoyancyForce,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_WaterDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ABoatPawn_Statics::NewProp_SubmersionDepth,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABoatPawn_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ABoatPawn_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APawn,
	(UObject* (*)())Z_Construct_UPackage__Script_ICPONDs,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ABoatPawn_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ABoatPawn_Statics::ClassParams = {
	&ABoatPawn::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ABoatPawn_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ABoatPawn_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ABoatPawn_Statics::Class_MetaDataParams), Z_Construct_UClass_ABoatPawn_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ABoatPawn()
{
	if (!Z_Registration_Info_UClass_ABoatPawn.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ABoatPawn.OuterSingleton, Z_Construct_UClass_ABoatPawn_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ABoatPawn.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ABoatPawn);
ABoatPawn::~ABoatPawn() {}
// ********** End Class ABoatPawn ******************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h__Script_ICPONDs_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ABoatPawn, ABoatPawn::StaticClass, TEXT("ABoatPawn"), &Z_Registration_Info_UClass_ABoatPawn, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ABoatPawn), 1052924419U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h__Script_ICPONDs_3686627134(TEXT("/Script/ICPONDs"),
	Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h__Script_ICPONDs_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h__Script_ICPONDs_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
