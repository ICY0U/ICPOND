// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "WaterManager.h"

#ifdef ICPONDS_WaterManager_generated_h
#error "WaterManager.generated.h already included, missing '#pragma once' in WaterManager.h"
#endif
#define ICPONDS_WaterManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AWaterManager ************************************************************
#define FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsLocationUnderwater); \
	DECLARE_FUNCTION(execGetWaterHeightAtLocation);


ICPONDS_API UClass* Z_Construct_UClass_AWaterManager_NoRegister();

#define FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAWaterManager(); \
	friend struct Z_Construct_UClass_AWaterManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ICPONDS_API UClass* Z_Construct_UClass_AWaterManager_NoRegister(); \
public: \
	DECLARE_CLASS2(AWaterManager, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ICPONDs"), Z_Construct_UClass_AWaterManager_NoRegister) \
	DECLARE_SERIALIZER(AWaterManager)


#define FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h_10_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AWaterManager(AWaterManager&&) = delete; \
	AWaterManager(const AWaterManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWaterManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWaterManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AWaterManager) \
	NO_API virtual ~AWaterManager();


#define FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h_7_PROLOG
#define FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h_10_INCLASS_NO_PURE_DECLS \
	FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AWaterManager;

// ********** End Class AWaterManager **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_WaterManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
