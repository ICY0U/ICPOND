using UnrealBuildTool;
using System.Collections.Generic;

public class ICPONDsEditorTarget : TargetRules
{
    public ICPONDsEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.AddRange(new string[] { "ICPONDs" });
    }
}
