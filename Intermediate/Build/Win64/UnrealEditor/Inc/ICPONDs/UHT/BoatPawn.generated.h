// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "BoatPawn.h"

#ifdef ICPONDS_BoatPawn_generated_h
#error "BoatPawn.generated.h already included, missing '#pragma once' in BoatPawn.h"
#endif
#define ICPONDS_BoatPawn_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ABoatPawn ****************************************************************
#define FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execResetBoatPosition); \
	DECLARE_FUNCTION(execSetWaterLevel);


ICPONDS_API UClass* Z_Construct_UClass_ABoatPawn_NoRegister();

#define FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABoatPawn(); \
	friend struct Z_Construct_UClass_ABoatPawn_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ICPONDS_API UClass* Z_Construct_UClass_ABoatPawn_NoRegister(); \
public: \
	DECLARE_CLASS2(ABoatPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ICPONDs"), Z_Construct_UClass_ABoatPawn_NoRegister) \
	DECLARE_SERIALIZER(ABoatPawn)


#define FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ABoatPawn(ABoatPawn&&) = delete; \
	ABoatPawn(const ABoatPawn&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABoatPawn); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABoatPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABoatPawn) \
	NO_API virtual ~ABoatPawn();


#define FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h_11_PROLOG
#define FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h_14_INCLASS_NO_PURE_DECLS \
	FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ABoatPawn;

// ********** End Class ABoatPawn ******************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_D_Documents_game_ICPONDS_ICPONDs__1__ICPONDs_Source_ICPONDs_BoatPawn_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
