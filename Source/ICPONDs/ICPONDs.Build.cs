using UnrealBuildTool;

public class ICPONDs : ModuleRules
{
    public ICPONDs(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { 
            "PhysicsCore", "Core", "CoreUObject", "Engine", "InputCore", 
            "EnhancedInput", "UMG", "AudioMixer", "AudioPlatformConfiguration"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { 
            "Slate", "SlateCore", "ToolMenus", "AudioMixer"
        });
    }
}
