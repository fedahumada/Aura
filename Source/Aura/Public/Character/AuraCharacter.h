// Fedahumada 

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"
class APlayerState;

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
	
	/*
	 * ~ INTERFACES
	 */
	//~ COMBAT INTERFACE
	virtual int32 GetPlayerLevel() override;

private:
	virtual void InitAbilityActorInfo() override;
};
