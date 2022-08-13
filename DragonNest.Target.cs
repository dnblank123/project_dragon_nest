using UnrealBuildTool;
using System.Collections.Generic;

public class DragonNestTarget : TargetRules
{
	public DragonNestTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "DragonNest" } );
	}
}
