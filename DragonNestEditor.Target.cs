using UnrealBuildTool;
using System.Collections.Generic;

public class DragonNestEditorTarget : TargetRules
{
	public DragonNestEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "DragonNest" } );
	}
}
