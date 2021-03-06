// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JamGameMode.h"
#include "JamGameInstance.generated.h"



class UUserWidget;


/**
 *
 */
UCLASS()
class JAMTEST_API UJamGameInstance : public UGameInstance
{
	GENERATED_BODY()

		const float MinErrorShowTime = 1.0f;
protected:
	//void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game")
		EGameStatus GameStatus = EGameStatus::Startup;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
		FName MainMenuName = "MainMenu";

	/**
	 * Tries to change current game status to the given value. If game status is same as current status returns false, otherwise true
	 */
	UFUNCTION(BlueprintCallable, Category = "Game")
		bool TryChangeStatus(EGameStatus InGameStatus);

	UFUNCTION(BlueprintImplementableEvent) //esposto come evento in bp. Alternativa che permette di implementare roba anche in c++: BlueprintNativeEvent
		void DestroySession();
	UFUNCTION(BlueprintImplementableEvent) //esposto come evento in bp. Alternativa che permette di implementare roba anche in c++: BlueprintNativeEvent
		void CreateSession();
	UFUNCTION(BlueprintImplementableEvent) //esposto come evento in bp. Alternativa che permette di implementare roba anche in c++: BlueprintNativeEvent
		void NetworkModeChanged();

	UPROPERTY()
		UUserWidget* MainMenuWidget;
	UPROPERTY()
		UUserWidget* ServerListWidget;
	UPROPERTY()
		UUserWidget* LoadingWidget;
	UPROPERTY()
		UUserWidget* ErrorDialogWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		bool bEnableLAN = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		int32 MaxConnections = 10;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> LoadingWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> ErrorDialogWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> ServerListWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Setup")
		int32 MinConnectedPlayersforGame = 2;
public:
	UFUNCTION(BlueprintCallable, Category = "Game")
		void StartPlayingState();
	UFUNCTION(BlueprintCallable, Category = "Lobby")
		void StartLobbyState();
	UFUNCTION(BlueprintCallable, Category = "Game")
		void CreateNetSession();
	UFUNCTION(BlueprintCallable, Category = "UI")
		void ShowAndOpenMainMenu(bool OpenLevel = true);
	UFUNCTION(BlueprintCallable, Category = "UI")
		void ShowLoadingScreen();
	UFUNCTION(BlueprintCallable, Category = "UI")
		void ShowServerList();
	UFUNCTION(BlueprintCallable, Category = "UI")
		void ShowErrorDialog(FText ErrorMsg, bool bDestroySession = false, float ShowTime = 1.0f);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game")
		FORCEINLINE FText& GetLastErrorMsg() { return LastErrorMsg; };

	UFUNCTION(BlueprintCallable, Category = "Lobby")
		void LobbyUpdatePlayersMonsterStatusLocal();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetNetworkMode(bool LanModeActive);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Setup")
		FORCEINLINE int32 GetMaxConnections() const { return MaxConnections; };
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Setup")
		FORCEINLINE int32 GetMinConnections() const { return MinConnectedPlayersforGame; };
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Setup")
		FORCEINLINE float GetRateoHumansPerMonstersInGame() const { return RateoHumansPerMonstersInGame; };

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game")
		FORCEINLINE FLobbyPlayerMonsterData GetPlayerLobbyData() const { return PlayerData; };
	UFUNCTION(BlueprintCallable, Category = "Game")
		void SetPlayerLobbyData(FLobbyPlayerMonsterData InValue) { PlayerData = InValue; };
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game")
		FORCEINLINE TArray<FLobbyPlayerMonsterData>& GetServerPlayerList() { return ServerPlayerList; };
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
		float RateoHumansPerMonstersInGame = 2.0f;

	UFUNCTION()
		UUserWidget* ShowWidget(EGameStatus InState, UUserWidget* ToInitialize, TSubclassOf<UUserWidget>& Class, bool bForceExec = true);
	UFUNCTION()
		void CollapseErrorDialog();
	UPROPERTY()
		FText LastErrorMsg;

	FTimerHandle ErrorTimerHandle;

	FLobbyPlayerMonsterData PlayerData;

	TArray<FLobbyPlayerMonsterData> ServerPlayerList;
};

