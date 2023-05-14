// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TerraIncursion : ModuleRules
{
	public TerraIncursion(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay" , 
			"AIModule", 
			"NavigationSystem", 
			"GameplayTasks"
        });

        PrivateIncludePaths.AddRange(new string[] { "Public" });

        CppStandard = CppStandardVersion.Cpp17;

    }
}
