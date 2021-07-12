// Copyright Amirreza Payandeh. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LostMarbleEditorTarget : TargetRules
{
	public LostMarbleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "LostMarble" } );
	}
}
