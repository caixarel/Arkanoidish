// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Shooter1Target : TargetRules
{
	public Shooter1Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Shooter1" } );
	}
}
