// Fill out your copyright notice in the Description page of Project Settings.


#include "Sequence/EvolutionSequenceDirector.h"
#include "MovieSceneSequence.h"
#include "MovieSceneBindingReferences.h"
#include "MovieScene.h"
void UEvolutionSequenceDirector::OnCreated()
{
	UE_LOG(LogTemp, Log, TEXT("Start UEvolutionSequenceDirector::OnCreated"));

	UMovieSceneSequence* MovieSceneSequence = GetSequence();
	UMovieScene* MovieScene = MovieSceneSequence->GetMovieScene();
	TArray<UMovieSceneTrack*> MovieSceneTracks = MovieScene->GetTracks();
	for (auto& Track : MovieSceneTracks)
	{
		FName TrackName = Track->GetTrackName();
		UE_LOG(LogTemp, Log, TEXT("%s"), *TrackName.ToString());
	}

	UE_LOG(LogTemp, Log, TEXT("END UEvolutionSequenceDirector::OnCreated"));
}