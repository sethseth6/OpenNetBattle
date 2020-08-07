#pragma once
#include "../bnAIState.h"
#include "bnNetworkBattleScene.h"
#include "bnNetPlayFlags.h"

class PlayerNetworkState : public AIState<Player>
{
private:
  bool isChargeHeld; /*!< Flag if player is holding down shoot button */
  CardAction* queuedAction; /*!< Movement takes priority. If there is an action queued, fire on next best frame*/
  NetPlayFlags& netflags;
  void QueueAction(Player& player);
public:

  /**
   * @brief isChargeHeld is set to false
   */
  PlayerNetworkState(NetPlayFlags&);

  /**
   * @brief deconstructor
   */
  ~PlayerNetworkState();

  /**
   * @brief Sets animation to IDLE
   * @param player player entity
   */
  void OnEnter(Player& player);

  /**
   * @brief Listens to input and manages shooting and moving animations
   * @param _elapsed
   * @param player
   */
  void OnUpdate(float _elapsed, Player& player);

  /**
   * @brief Sets player entity charge component to false
   * @param player player entity
   */
  void OnLeave(Player& player);
};