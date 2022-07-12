// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
AMainCharacter::AMainCharacter() :
	BaseTurnRate(50.f),
	BaseLookUpRate(50.f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/**Creating the camera boom*/
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	/**Creating the follow camera*/
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//Don't rotate when the controller rotates. Let the controller only affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->JumpZVelocity = 450.f;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

}

/**function definition for the player movement to the forward/backward*/
void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//find which way is foward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		AddMovementInput(Direction, Value);
	}
}

/**function definition for the player movement to the right/left*/
void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//find which way is foward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, Value);
	}
}

/**function definition for the player look right*/
void AMainCharacter::TurnRight(float Value)
{
	AddControllerYawInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

/**function definition for the player look up*/
void AMainCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
/**function definition for the player start walk*/
void AMainCharacter::StartWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = 110.f;
}
/**function definition for the player end walk*/
void AMainCharacter::EndWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}
/**function definition for the player start sprint*/
void AMainCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
}
/**function definition for the player end sprint*/
void AMainCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}


// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/**checking player inputs*/
	check(PlayerInputComponent);
	/**calling MoveForward() function when user inputs W/S*/
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	/**calling MoveRight() function when user inputs D/A*/
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	/**calling LookUp() function when user inputs Mouse Y*/
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::LookUp);
	/**calling TurnRight() function when user inputs Mouse X*/
	PlayerInputComponent->BindAxis("TurnRight", this, &AMainCharacter::TurnRight);

	/**calling StartWalk() function when user press left alt*/
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AMainCharacter::StartWalk);
	/**calling EndWalk() function when user release left alt*/
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &AMainCharacter::EndWalk);
	/**calling StartSprint() function when user press left shift*/
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::StartSprint);
	/**calling EndSprint() function when user release left shift*/
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::EndSprint);
}

