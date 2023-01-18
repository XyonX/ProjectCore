// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectCore : ModuleRules
{
	public ProjectCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","UMG", "HeadMountedDisplay" , "GameplayTags","OnlineSubsystemSteam","OnlineSubsystem", "GameplayAbilities","AIModule", "GameplayTasks", "NavigationSystem" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
