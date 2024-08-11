// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AI_CORE : ModuleRules
{
	public AI_CORE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "GameplayTasks", "UMG"});
        
	}
}
