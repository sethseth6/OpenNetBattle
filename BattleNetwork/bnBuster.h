#pragma once
#include "bnSpell.h"
#include "bnAnimationComponent.h"

/**
 * @class Buster
 * @author mav
 * @date 05/05/19
 * @brief Classic buster attack 
 * 
 * NOTE: This comes from legacy code and could be improved
 */
class Buster : public Spell {
public:
  /**
   * @brief If _charged is true, deals 10 damage
   */
  Buster(Team _team,bool _charged, int damage);
  ~Buster() override;

  void OnUpdate(double _elapsed) override;
  
  bool CanMoveTo(Battle::Tile* next) override;

  void OnDelete() override;

  /**
   * @brief Deal impact damage
   * @param _entity
   */
  void Attack(Character* _entity) override;

private:
  bool isCharged;
  bool spawnGuard;
  Character* contact;
  int damage;
  double cooldown{};
  float random; // offset
  float hitHeight;
  std::shared_ptr<sf::Texture> texture;
  float progress;
  AnimationComponent* animationComponent;
};