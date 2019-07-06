#include "bnWave.h"
#include "bnTile.h"
#include "bnField.h"
#include "bnSharedHitBox.h"
#include "bnTextureResourceManager.h"
#include "bnAudioResourceManager.h"

Wave::Wave(Field* _field, Team _team, double speed) : Spell(_field, _team) {
  SetLayer(0);

  setTexture(*TEXTURES.GetTexture(TextureType::SPELL_WAVE));
  this->speed = speed;

  //Components setup and load
  auto onFinish = [this]() {
    this->Delete();
    if(this->GetTile()->GetX() > 1) {
        auto* wave = new Wave(this->GetField(), this->GetTeam(), this->speed);
        wave->SetDirection(this->GetDirection());

        this->GetField()->AddEntity(*wave, GetTile()->GetX()-1, GetTile()->GetY());
    }
  };

  animation = new AnimationComponent(this);
  this->RegisterComponent(animation);

  animation->Setup("resources/spells/spell_wave.animation");
  animation->Load();
  animation->SetAnimation("DEFAULT", Animate::Mode::Loop, onFinish);
  animation->SetPlaybackSpeed(speed);
  animation->OnUpdate(0);

  auto props = Hit::DefaultProperties;
  props.damage = 10;
  this->SetHitboxProperties(props);

  AUDIO.Play(AudioType::WAVE);

  EnableTileHighlight(true);
}

Wave::~Wave() {
}

void Wave::OnUpdate(float _elapsed) {
Logger::Log(std::string("wave team: ") + std::to_string((int)GetTeam()));

  int lr = (this->GetDirection() == Direction::LEFT) ? 1 : -1;
  setScale(2.f*(float)lr, 2.f);

  setPosition(GetTile()->getPosition().x, GetTile()->getPosition().y);

  tile->AffectEntities(this);
}

bool Wave::Move(Direction _direction) {
  return false;
}

void Wave::Attack(Character* _entity) {
  Logger::Log("wave attack");

  _entity->Hit(GetHitboxProperties());
}
