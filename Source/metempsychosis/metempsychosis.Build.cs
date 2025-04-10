// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class metempsychosis : ModuleRules
{
	public metempsychosis(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","AIModule","GameplayTasks","NavigationSystem" });
	}
}
