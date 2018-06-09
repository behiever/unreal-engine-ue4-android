// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;

public class iTOPSample : ModuleRules
{
	public iTOPSample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","Json", "JsonUtilities" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
         
        		// Uncomment if you are using Slate UI
        		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        		PrivateDependencyModuleNames.AddRange(new string[] { "iTOP" });//添加iTop的UE4插件
 
	}
}
