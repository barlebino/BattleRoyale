#include "EnemyComponent.hpp"

#include "Scene/Scene.hpp"
#include "Util/Util.hpp"
#include "Component/StatComponents/StatComponents.hpp"
#include "System/GameInterface.hpp"
#include "System/SoundSystem.hpp"
#include "Component/SpatialComponents/SpatialComponent.hpp"
#include "Component/CollisionComponents/BounderComponent.hpp"
#include "Component/PlayerComponents/PlayerComponent.hpp"
#include "System/ParticleSystem.hpp"
#include "Component/ParticleComponents/ParticleAssasinComponent.hpp"



EnemyComponent::EnemyComponent(GameObject & gameObject) :
    Component(gameObject),
    m_body(nullptr),
    m_head(nullptr),
    m_health(nullptr),
    m_damaged(false),
    m_soundCooldown(0.0f)
{}

void EnemyComponent::init() {
    const auto & spatials(gameObject().getComponentsByType<SpatialComponent>());
    assert(spatials.size() >= 2);
    m_body = spatials[0];
    m_head = spatials[1];
    assert(m_health = gameObject().getComponentByType<HealthComponent>());
}

void EnemyComponent::update(float dt) {
    m_soundCooldown -= dt;
    if (m_health->value() < 0.5f) {
        SoundSystem::playSound3D("Enemy_death.wav", m_head->position());

        GameObject & obj(Scene::createGameObject());
        SpatialComponent & spat(Scene::addComponent<SpatialComponent>(obj, m_body->position()));
        ParticleSystem::addBodyExplosionPC(spat);
        Scene::addComponent<ParticleAssasinComponent>(obj);

        Scene::destroyGameObject(this->gameObject());
        return;
    }
    else if (m_damaged && m_soundCooldown <= 0.0f) {
        SoundSystem::playSound3D("grunt1.wav", m_head->position());
        m_soundCooldown = 0.25f;
    }
    m_damaged = false;

    // Head tracking
    glm::vec3 pos(m_body->position());
    glm::vec3 playerPos(GameInterface::getPlayer().getSpatial()->position());
    m_body->lookAt(glm::vec3(playerPos.x, pos.y, playerPos.z), glm::vec3(0.0f, 1.0f, 0.0f));
    m_head->lookAt(playerPos, glm::vec3(0.0f, 1.0f, 0.0f));
}

void EnemyComponent::damage(float damage) {
    m_health->changeValue(-damage);
    m_damaged = true;
}



BasicEnemyComponent::BasicEnemyComponent(GameObject & gameObject, float meleeDamage) :
    EnemyComponent(gameObject),
    m_meleeDamage(meleeDamage)
{}

void BasicEnemyComponent::init() {
    EnemyComponent::init();
    
    auto collisionCallback([&](const Message & msg_) {
        const CollisionMessage & msg(static_cast<const CollisionMessage &>(msg_));
        // Melee damage to player
        PlayerComponent * player;
        if (player = msg.bounder2.gameObject().getComponentByType<PlayerComponent>()) {
            player->damage(m_meleeDamage);
        }
    });
    Scene::addReceiver<CollisionMessage>(&gameObject(), collisionCallback);
}
