#pragma once
#include "bnArtifact.h"
#include "bnAnimationComponent.h"

class Field;
/**
 * @class Explosion
 * @author mav
 * @date 04/05/19
 * @brief Explosion spawns as many explosions over time if the count is > 1
 * 
 * First explosion is always centered on the tile and on the top-most layer
 * 
 * If the number of explosions is > 1 the following explosions will be set on the
 * bottom layer and offset by a random amount to recreate the effect seen in the game
 */
class Explosion : public Artifact
{
private:
  AnimationComponent* animationComponent; /*!< Animate the explosion */
  int numOfExplosions; /*!< Once the count reaches this number, the effect is over */
  sf::Vector2f offset; /*!< Explosion children are placed randomly around the spawn area */
  int count; /*!< Used by root to keep track of explosions left */
  Explosion* root; /*!< The explosion that starts the chain */
  double playbackSpeed; /*!< The speed of the explosion effect. Bosses have higher speeds */
  
   /** 
   * @brief Used internally by root explosions to create childen explosions
   * @param copy the root explosion to copy settings from
   */
  Explosion(const Explosion& copy);

public:
  /**
   * @brief Create an explosion chain effect with numOfExplosions=1 and playbackSpeed=0.55 defaults
   */
  Explosion(Field* _field, Team _team, int _numOfExplosions=1, double _playbackSpeed=0.55);
  
  ~Explosion();

  /**
   * @brief If root increment count is size of numOfExplosions, delete and stop the chain 
   * @param _elapsed in seconds
   */
  virtual void OnUpdate(float _elapsed);
  
  /**
   * @brief Explosion doesnt move
   * @param _direction ignored
   * @return false
   */
  virtual bool Move(Direction _direction) { return false; }

  /**
   * @brief Used by root. Increment the number of explosions
   */
  void IncrementExplosionCount();

};

