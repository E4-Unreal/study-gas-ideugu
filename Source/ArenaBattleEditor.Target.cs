// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ArenaBattleEditorTarget : TargetRules
{
	public ArenaBattleEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        ExtraModuleNames.AddRange(new string[] { "ArenaBattle", "ArenaBattleGAS" });
    }
}
