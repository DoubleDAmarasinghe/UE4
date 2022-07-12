// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class GTA_SAMPLE_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**function for the player movement to the forward/backward*/
	void MoveForward(float Value);
	/**function for the player movement to the right/left*/
	void MoveRight(float Value);
	/**function for the look left/right around the player*/
	void TurnRight(float Value);
	/**function for the look up/down around the player*/
	void LookUp(float Value);

	/**function for the player start walk*/
	void StartWalk();
	/**function for the player end walk*/
	void EndWalk();
	/**function for the player start sprint*/
	void StartSprint();
	/**function for the player end sprint*/
	void EndSprint();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/**Posisioning the camera behind the character*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	/**Camera that follows the player*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	/**variable for the look up/down sesevity*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float BaseLookUpRate;
	/**variable for the look left/right sesevity*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (allowPrivateAccess = "true"))
		float BaseTurnRate;
public:
	/**public getter for the camera boom*/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/**public getter for the follow camera*/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
