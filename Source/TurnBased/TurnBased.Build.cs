// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TurnBased : ModuleRules
{
	public TurnBased(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
        
        PrivateDependencyModuleNames.AddRange(new string[]{ "GameplayAbilities" , "GameplayTags" , "GameplayTasks"});
    }
}
