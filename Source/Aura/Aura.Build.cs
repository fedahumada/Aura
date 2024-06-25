// Fedahumada 

using UnrealBuildTool;

public class Aura : ModuleRules
{
	public Aura(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities"});

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks", "NavigationSystem", "Niagara", "AIModule"});

	}
}
