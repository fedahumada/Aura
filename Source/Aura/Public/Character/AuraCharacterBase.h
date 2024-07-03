// Fedahumada 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"
class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;
class UAnimMontage;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void Die() override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();


	/*
  * MONTAGES
  */
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TArray<FTaggedMontage> AttackMontages;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	/*
	  * ATTRIBUTES
	  */
	virtual void InitializeDefaultAttributes() const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	/*
	  * GAMEPLAY EFFECTS
	  */
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	/*
* GAMEPLAY ABILITIES
*/
	void AddCharacterAbilities() const;


	/*
	* MISC
	*/

	int32 MinionCount = 0;
	
	//~ Combat Effects
	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeLine(UMaterialInstanceDynamic* MaterialInstanceDynamic);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeLine(UMaterialInstanceDynamic* MaterialInstanceDynamic);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	UPROPERTY(EditAnywhere,Category="Combat")
	UNiagaraSystem* BloodEffect;

	UPROPERTY(EditAnywhere,Category="Combat")
	USoundBase* DeathSound;

	//~ Sockets 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere,Category="Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere,Category="Combat")
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere,Category="Combat")
	FName RightHandSocketName;

	UPROPERTY(EditAnywhere,Category="Combat")
	FName TailSocketName;
	
	//~ Character Status
	bool bIsDead = false;


	/*
	  * INTERFACES
	  */
	//~ Combat Interface
	virtual AActor* GetAvatar_Implementation() override;

	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;

	virtual bool IsDead_Implementation() const override;

	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;

	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;

	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	
	virtual int32 GetMinionCount_Implementation() override;

	virtual void IncrementMinionCount_Implementation(int32 Amount) override;
	
private:
	/*
	* GAMEPLAY ABILITIES
	*/
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilitiesList;

	
	/*
  * MONTAGES
  */
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
