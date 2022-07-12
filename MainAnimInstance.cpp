// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMainAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if(MainCharacter == nullptr)
	{
		MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	}

	if(MainCharacter)
	{
		FVector Velocity{ MainCharacter->GetVelocity() };
		Velocity.Z = 0;
		speed = Velocity.Size();

		if(MainCharacter->GetCharacterMovement()->MaxWalkSpeed == 110.f)
		{
			speed = 0;
		}
		if(MainCharacter->GetCharacterMovement()->MaxWalkSpeed == 600.f)
		{
			speed = 50;
		}
		if(MainCharacter->GetCharacterMovement()->MaxWalkSpeed == 1000.f)
		{
			speed = 100;
		}

		FRotator AimRotation = MainCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(MainCharacter->GetVelocity());
		movementOffSetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if (MainCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

	}

}

void UMainAnimInstance::NativeInitializeAnimation()
{
	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
}
