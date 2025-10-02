using UnrealBuildTool;

public class ICPONDs : ModuleRules
{
    public ICPONDs(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "PhysicsCore",
            "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
