#include "bnForte.h"
#include "bnExplodeState.h"
#include "bnField.h"
#include "bnBuster.h"
#include "bnTextureResourceManager.h"
#include "bnAudioResourceManager.h"
#include "bnEngine.h"
#include "bnLogger.h"

const float COPY_DROP_COOLDOWN = 0.15f; // in seconds

const std::string RESOURCE_PATH = "resources/navis/forte/forte.animation";

Forte::Forte() : Player()
{
  chargeComponent.setPosition(0, -40.0f);
  SetName("Bass");
  SetLayer(0);
  team = Team::RED;
  this->SetElement(Element::NONE);

  this->SetBusterDamage(3);
  this->SetChargedBusterDamage(20);

  animationComponent->Setup(RESOURCE_PATH);
  animationComponent->Reload();

  setTexture(*TEXTURES.GetTexture(TextureType::NAVI_FORTE_ATLAS));

  this->SetHealth(2000);

  SetFloatShoe(true);

  aura = new Aura(Aura::Type::AURA_200, this);
  this->RegisterComponent(aura);
  //aura->setPosition(0, -20.0f);

  dropCooldown = COPY_DROP_COOLDOWN;

  // Bass slides around lookin pretty slick
  this->EnablePlayerControllerSlideMovementBehavior(true);

  SetBusterDamage(3);
  SetChargedBusterDamage(30);
  chargeComponent.SetFullyChargedColor(sf::Color::Green);

}

Forte::~Forte()
{
  this->FreeComponentByID(aura->GetID());
  delete aura;
  aura = nullptr;
}

const float Forte::GetHitHeight() const
{
  return 160.0f;
}

void Forte::OnUpdate(float _elapsed)
{
  dropCooldown -= _elapsed;

  // Continue with the parent class routine
  Player::OnUpdate(_elapsed);

  // We are moving
  if (this->GetNextTile()) {
    if (dropCooldown <= 0) {
      auto fx = new MoveEffect(field);
      field->AddEntity(*fx, *this->GetTile());
    }
    else {
      dropCooldown = COPY_DROP_COOLDOWN;
    }
  }
}

void Forte::OnDelete()
{
  Player::OnDelete();
}

int Forte::MoveEffect::counter = 0;

Forte::MoveEffect::MoveEffect(Field* field) : Artifact(field)
{
  setTexture(*TEXTURES.GetTexture(TextureType::NAVI_FORTE_ATLAS));

  SetLayer(1);
  this->setScale(2.f, 2.f);

  animationComponent = (AnimationComponent*)RegisterComponent(new AnimationComponent(this));
  animationComponent->Setup(RESOURCE_PATH);
  animationComponent->Reload();
  animationComponent->SetAnimation("COPY");

  index = ++counter;

  animationComponent->SetFrame((counter % 2));
}

Forte::MoveEffect::~MoveEffect()
{
}

void Forte::MoveEffect::OnUpdate(float _elapsed)
{
  elapsed += _elapsed;
  auto delta = 1.0f - swoosh::ease::linear(elapsed, 0.1f, 1.0f);

  this->SetAlpha(int(delta*125));

  if (delta <= 0.0f) {
    this->Delete();
  }
}
