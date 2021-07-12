// Copyright Amirreza Payandeh. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LostMarbleTarget : TargetRules
{
	public LostMarbleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LostMarble" } );
	}
}
