#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Inimigo.h"
#include "Inventario.h"
#include "Item.h"
#include "Jogador.h"
#include "Mapa.h"
#include "Objetivo.h"
#include "Plataforma.h"

static const float VIEW_HEIGHT = 322.0f;

using namespace std;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int teclaPressionada()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        return 1;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        return 2;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        return 3;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        return 4;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        return 5;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        return 6;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        return 7;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        return 8;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
        return 9;
    else
        return 0;
}

float obtemPosX(Jogador* j)
{
    return j->getX();
}

float obtemPosY(Jogador* j)
{
    return j->getY();
}

///----------------------------------------------------------------------------------///
///                                  EXERCICIOS                                      ///
///----------------------------------------------------------------------------------///

///EXERCICIO 1
typedef struct
{
    float posicaoJogador[2];
    int campoDeVisao;
}DadosJogador;

typedef struct
{
    int mapa[TAMANHO_MAPA_X][TAMANHO_MAPA_Y];
    int coordenadasJogadorX;
    int coordenadasJogadorY;
    DadosJogador dados;
}Minimapa;

///EXERCICIO 2
DadosJogador atualizaDadosJogador(Jogador* j)
{
    DadosJogador dados;
    dados.posicaoJogador[0] = obtemPosX(j);
    dados.posicaoJogador[1] = obtemPosY(j);
    dados.campoDeVisao = 48 * 10;

    return dados;
}

void atualizaDadosJogadorMapa(Minimapa& minimapa, Jogador* j)
{
    minimapa.dados = atualizaDadosJogador(j);
    minimapa.coordenadasJogadorX = int(minimapa.dados.posicaoJogador[0] / TAMANHO_BLOCOS);
    minimapa.coordenadasJogadorY = int(minimapa.dados.posicaoJogador[1] / TAMANHO_BLOCOS);
}

///EXERCICIO 3
void atualizaMinimapa(Minimapa& minimapa)
{
    ///EXERCICIO 4
    float centroX, centroY, jogadorX, jogadorY;
    jogadorX = minimapa.dados.posicaoJogador[0];
    jogadorY = minimapa.dados.posicaoJogador[1];
    ///

    for(int i = 0; i < TAMANHO_MAPA_X; i++)
    {
        for(int j = 0; j < TAMANHO_MAPA_Y; j++)
        {
            minimapa.mapa[i][j] = 2; ///NO EXERCICIO 3 ELE RECEBE 0 PARA SER TRANSPARENTE

            ///EXERCICIO 4
            centroX = i * TAMANHO_BLOCOS + TAMANHO_BLOCOS / 2;
            centroY = j * TAMANHO_BLOCOS + TAMANHO_BLOCOS / 2;

            if(sqrt(pow(jogadorX - centroX, 2) + pow(jogadorY - centroY, 2)) < minimapa.dados.campoDeVisao)
                minimapa.mapa[i][j] = 0;
            ///
        }
    }
    minimapa.mapa[minimapa.coordenadasJogadorX][minimapa.coordenadasJogadorY] = 1;
}

///----------------------------------------------------------------------------------///
///                                                                                  ///
///----------------------------------------------------------------------------------///

int main()
{
    //VARIAVEIS DA CONFIGURACAO
    sf::RenderWindow window(sf::VideoMode(800, 512), "Jogo Aula 04", sf::Style::Close);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    //VARIAVEL EXERCICIO
    Minimapa minimapa;

    //VARIAVEIS DO JOGO
    sf::Texture texturaJogador;
    texturaJogador.loadFromFile("texturas/jogador.png");
    sf::Texture texturaMapa;
    texturaMapa.loadFromFile("texturas/mapa.png");
    sf::Texture texturaInimigo;
    texturaInimigo.loadFromFile("texturas/inimigo.png");
    sf::Texture texturaInventario;
    texturaInventario.loadFromFile("texturas/inventario.png");
    sf::Texture texturaItem;
    texturaItem.loadFromFile("texturas/itens.png");
    sf::Texture texturaIndice;
    texturaIndice.loadFromFile("texturas/indices.png");
    sf::Texture texturaObjetivo;
    texturaObjetivo.loadFromFile("texturas/amigo.png");

    Mapa mapa(&texturaMapa, sf::Vector2u(16, 16), &texturaInventario, sf::Vector2u(17, 10));

    Jogador jogador(&texturaJogador, sf::Vector2u(13, 21), 0.3f, 180.0f);

    Inventario inventario(&texturaInventario, sf::Vector2u(17, 10), &texturaItem, sf::Vector2u(16, 16), &texturaIndice, sf::Vector2u(4, 1));

    Objetivo objetivo(&texturaObjetivo, sf::Vector2u(13, 21), &texturaInventario, sf::Vector2u(17, 10), &texturaItem, sf::Vector2u(16, 16));

    std::vector<Plataforma> plataformas;
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(384.0f, 384.0f), sf::Vector2f(96.0f, 96.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(480.0f, 1104.0f), sf::Vector2f(192.0f, 384.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(624.0f, 528.0f), sf::Vector2f(288.0f, 192.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(864.0f, 624.0f), sf::Vector2f(192.0f, 384.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(1056.0f, 1296.0f), sf::Vector2f(192.0f, 384.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(1248.0f, 1200.0f), sf::Vector2f(192.0f, 192.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(1296.0f, 576.0f), sf::Vector2f(192.0f, 192.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(768.0f, 1104.0f), sf::Vector2f(192.0f, 192.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(1128.0f, 888.0f), sf::Vector2f(144.0f, 144.0f)));
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(1392.0f, 1512.0f), sf::Vector2f(96.0f, 144.0f)));

    std::vector<Inimigo> inimigos;
        inimigos.push_back(Inimigo(&texturaInimigo, sf::Vector2u(13, 21), 0.3f, 80.0f, 0, 1));

    std::vector<Item> itens;
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(1296.0f, 1008.0f), 'a'));///27 21
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(1248.0f, 1344.0f), 'a'));///26 28
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(1488.0f, 1536.0f), 'a'));///31 32
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(336.0f , 672.0f ), 'd'));///7  14
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(288.0f , 1056.0f), 'd'));///6  22
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(960.0f , 1008.0f), 'f'));///18 24
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(1488.0f, 1248.0f), 'g'));///6  8
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(318.0f , 1152.0f), 'g'));///6  24
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(960.0f , 864.0f ), 'i'));///20 18
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(480.0f , 336.0f ), 'i'));///10 7
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(624.0f , 1440.0f), 'i'));///6  28
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(1392.0f, 720.0f ), 'i'));///29 15
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(288.0f , 288.0f ), 'i'));///6  6
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(336.0f , 1488.0f), 'i'));///7  31
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(1056.0f, 672.0f ), 'i'));///22 14
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(1248.0f, 384.0f ), 'i'));///8  15
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(624.0f , 1056.0f), 'i'));///13 22
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(1056.0f, 288.0f ), 'i'));///22 6
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(624.0f , 720.0f ), 'i'));///13 15
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(672.0f , 912.0f ), 'i'));///14 19
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(768.0f , 288.0f ), 'i'));///16 6
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(480.0f , 768.0f ), 'i'));///10 16
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(864.0f , 1248.0f), 'i'));///18 26
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(1440.0f, 288.0f ), 'i'));///30 6
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(288.0f , 864.0f ), 'i'));///6  18
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(912.0f , 1536.0f), 'i'));///19 32
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(1392.0f, 720.0f ), 'i'));///29 15

    //CONFIGURA TEMPO
    float deltaTempo = 0.0f;
    sf::Clock clock;

    //DELAY TECLA
    float delay = 1;

    //CONFIGURA VIEW
    ResizeView(window, view);

    while(window.isOpen())
    {
        ////CONFIGURACOES GERAIS

        deltaTempo = clock.restart().asSeconds();
        if(deltaTempo > 1.0f / 20.0f)
            deltaTempo = 1.0f / 20.0f;

        if(delay > 0)
            delay -= deltaTempo;
        else
            delay = 0;

        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        ////JOGO

        //ITENS

        for(unsigned int i = 0; i < itens.size(); i++)
        {
            Item& item = itens[i];

            //PEGAR ITEM
            if(item.getColisor().checaColisao(jogador.getColisor()) && sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !item.getStatus())
            {
                item.coletou();
                inventario.pegouItem(item.getTipo());
            }

            //ENTREGAR ITEM
            if(item.getColisor().checaColisao(objetivo.getColisorItens()) && !item.getStatus() && objetivo.getNumRecebidos() != 5)
            {
                item.coletou();
                objetivo.recebeuItem(item.getTipo());
            }
        }

        int tecla = teclaPressionada();

        if(tecla != 0 && delay == 0)
        {
            char tipo = inventario.soltouItem(tecla);
            if(tipo != ' ')
            {
                for(unsigned int i = 0; i < itens.size(); i++)
                {
                    Item& item = itens[i];
                    if(item.getTipo() == tipo && item.getStatus())
                    {
                        item.soltou(jogador.getPosicao().x, jogador.getPosicao().y - 20);
                        break;
                    }
                }
            delay = 0.6;
            }
        }

        //COLISOES

        char direcao;

        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plataforma = plataformas[i];

            //JOGADOR x PLATAFORMA
            plataforma.getColisor().checaColisaoJogadorPlataforma(jogador.getColisor());

            for(unsigned int j = 0; j < inimigos.size(); j++)
            {
                Inimigo& inimigo = inimigos[j];

                //INIMIGO x PLATAFORMA
                direcao = plataforma.getColisor().checaColisaoInimigoPlataforma(inimigo.getColisor());
                switch(direcao)
                {
                    case 'c':
                        inimigo.setSentidoY(1);
                        break;
                    case 'b':
                        inimigo.setSentidoY(-1);
                        break;
                    case 'd':
                        inimigo.setSentidoX(-1);
                        break;
                    case 'e':
                        inimigo.setSentidoX(1);
                        break;
                    default:
                        break;
                }

                //INIMIGO x JOGADOR
                if(jogador.getStatus())
                    jogador.setStatus(!jogador.getColisor().checaColisao(inimigo.getColisor()));
            }
        }

        objetivo.getColisorPlayer().checaColisaoJogadorPlataforma(jogador.getColisor());

        //MOVIMENTACAO

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            inimigo.atualiza(deltaTempo);
        }

        if(!objetivo.getTerminou())
            jogador.atualiza(deltaTempo);

        //ATUALIZA CONFIGURACOES

        view.setCenter(jogador.getPosicao());
        window.setView(view);
        window.clear(sf::Color(150,150,150));

        //MINIMAPA

        atualizaDadosJogadorMapa(minimapa, &jogador);
        atualizaMinimapa(minimapa);
        for(unsigned int i = 0; i < itens.size(); i++)
        {
            Item& item = itens[i];
            int x = int(item.getX() / TAMANHO_BLOCOS);
            int y = int(item.getY() / TAMANHO_BLOCOS);
            if(!item.getStatus() && minimapa.mapa[x][y] != 1 && minimapa.mapa[x][y] != 2)
                minimapa.mapa[x][y] = 3;
        }
        cout << "( " << int(jogador.getX()/TAMANHO_BLOCOS) << " , " << int(jogador.getY()/TAMANHO_BLOCOS) << " )" << endl;

        //DESENHA OS OBJETOS

        mapa.desenha(window);

        for(unsigned int i = 0; i < itens.size(); i++)
        {
            Item& item = itens[i];
            item.desenha(window);
        }

        bool vivo = jogador.getStatus();
        bool naFrente = (objetivo.getY() > jogador.getY());

        if(!vivo)
            jogador.desenha(window);

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            if(inimigo.getY() < jogador.getY())
                inimigo.desenha(window);
        }

        if(!naFrente)
            objetivo.desenha(window);

        if(vivo)
            jogador.desenha(window);

        if(naFrente)
            objetivo.desenha(window);

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            if(inimigo.getY() > jogador.getY())
                inimigo.desenha(window);
        }

        if(!objetivo.getTerminou())
        {
            inventario.desenha(window, view.getCenter());
            mapa.desenhaMinimapa(window, view.getCenter(), minimapa.mapa);
        }

        //FINAL DO JOGO

        if(objetivo.getTerminou())
        {
            objetivo.fimDeJogo();
            objetivo.desenhaFinal(window, view.getCenter());
        }

        ////
        window.display();
    }

    return 0;
}

