// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ATB_Rogue : ModuleRules
{
	public ATB_Rogue(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
            "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
                "UMG","AIModule","Slate", "SlateCore", "NavigationSystem",
            "MoviePlayer","MovieScene","LevelSequence"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[]
		{
			this.Name
		});
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
