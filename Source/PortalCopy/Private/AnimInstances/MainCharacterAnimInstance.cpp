#include "AnimInstances/MainCharacterAnimInstance.h"
#include "PortalCopy/Public/Characters/MainCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	if (MainCharacter)
	{
		CharacterMovement = MainCharacter->GetCharacterMovement();
	}
}


void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (CharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovement->Velocity);
		IsFalling = CharacterMovement->IsFalling();
	}
}