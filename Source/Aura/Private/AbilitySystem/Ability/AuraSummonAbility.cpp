// Fedahumada 


#include "AbilitySystem/Ability/AuraSummonAbility.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector ForwardVector = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector LeftSpread = ForwardVector.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	const float SectionAngle = SpawnSpread / NumMinions;

	TArray<FVector> SpawnLocations;
	for (int32 i=0; i<NumMinions; i++)
	{
		const FVector Direction = LeftSpread.RotateAngleAxis(SectionAngle * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0.f, 0.f, 400.f), ChosenSpawnLocation - FVector(0.f, 0.f, 400.f), ECC_Visibility);
		if (Hit.bBlockingHit) ChosenSpawnLocation = Hit.ImpactPoint;
		
		SpawnLocations.Add(ChosenSpawnLocation);
	}

	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];	
}
