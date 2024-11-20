// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/CursorEffect.h"
#include "CursorEffect.h"

ACursorEffect::ACursorEffect()
{
	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemAsset(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireBall.P_ky_fireBall'"));
	UParticleSystem* InParticleSystem = nullptr;
	if (ParticleSystemAsset.Succeeded())
	{
		InParticleSystem = ParticleSystemAsset.Object;
	}
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
	ParticleSystemComponent->SetTemplate(InParticleSystem);
	//ParticleSystemComponent->OnSystemFinished.AddDynamic(this, &ThisClass::OnParticleSystemFinished);
}

void ACursorEffect::BeginPlay()
{
	Super::BeginPlay();

}

void ACursorEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACursorEffect::PlayEffect()
{
	SetLifeSpan(0);
	SetLifeSpan(0.5f);
}

void ACursorEffect::OnParticleSystemFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}