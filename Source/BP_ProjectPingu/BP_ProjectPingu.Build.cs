// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BP_ProjectPingu : ModuleRules
{
	public BP_ProjectPingu(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
