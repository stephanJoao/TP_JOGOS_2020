#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include <SFML/Graphics.hpp>
#include "Colisor.h"


class Plataforma
{
public:
    Plataforma(sf::Texture* textura, sf::Vector2f posicao, sf::Vector2f tamanho);
    virtual ~Plataforma();

    void desenha(sf::RenderWindow& window);

    Colisor getColisor() { return Colisor(corpo); };

private:
    sf::RectangleShape corpo;
};

#endif // Plataforma_H
