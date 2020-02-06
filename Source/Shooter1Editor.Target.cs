// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Shooter1EditorTarget : TargetRules
{
	public Shooter1EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Shooter1" } );
	}
}
