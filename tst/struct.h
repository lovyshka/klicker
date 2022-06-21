#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


using namespace sf;
/*создаем спецификацию класса*/
struct Game {
    int goodClicks = 0; //<кол-во попаданий по квадрату*/
    int totalClicks = -1; /*кол-во общих кликов*/
    int x; /*координата х*/
    int y; /*координата у*/
    int size; /*переменная отвечающее за размер квадрата*/
    sf::Font font; /*шрифт*/
    sf::Text txt; /*текст*/
    sf::RectangleShape target; /*поле отвечающее за наш объект(квадрат)*/
    sf::Text leftTime; /*пременная  - оставшееся время*/
    sf::Clock timer; /*переменная - время прошедшее с последнего клика или начала игры*/


    Game() : x(400), y(400), size(50) {
        target.setPosition(x, y);
        target.setSize(sf::Vector2f(size, size));
        target.setFillColor(sf::Color::Green);
        font.loadFromFile("Fonts/Russian.ttf");
        filtTextParam(txt);
        txt.setString(std::string("0/0"));
        filtTextParam(leftTime);
        leftTime.setPosition(1800, 10);
        leftTime.setString(std::string("5.0 s"));
    }

/**
 * Применяет к тексту методы из библиотеки SFML
 * @param txt - переменная которая отвечает за текст, который отображается на экране во время игры
 */
    void filtTextParam(sf::Text &txt) const {
        txt.setFont(font);
        txt.setCharacterSize(30);
        txt.setFillColor(sf::Color::Yellow);
        txt.setOutlineColor(sf::Color::Black);
        txt.setOutlineThickness(1);
        txt.setPosition(10, 10);
        txt.setStyle(sf::Text::Bold);
    }

/**
 * функция отрисовки объекта на экране, в нее передается window
 * @param window - окно, созданное в функции main описанная в main.cpp
 */
    void draw(sf::RenderWindow &window) {
        window.clear(sf::Color::White); /*окрашиваем окно в белый для дальнейшего отображения объектов*/
        window.draw(target); /*отрисовываем наш объект*/
        window.draw(txt); /*отрисовываем текст*/
        auto t = timer.getElapsedTime().asSeconds(); /*создаем поле t для сохранения в нем времени*/
        auto dt = 5 - t; /*создаем поле для сохранения оставшегося времени*/
        int dt2 = 10 * dt; /*создаем поле для дальнейшего удобного отображения*/
        int a = dt2 / 10; /*целые секунды*/
        int b = dt2 % 10; /*десятые секунды*/
        leftTime.setString(std::to_string(a) + "." + std::to_string(b) + " s"); /*выводим через точку*/
        window.draw(leftTime); /*отрисовываем оставшееся время*/
    }

/**
 * функция для генерации объекта в случайном месте экрана
 */
    void newrect() {
        x += 9999;
        y += 9999;
        x = x % 1820; /*берем остаток от деления на 1820, чтобы объект появлялся в доступном для пользователя месте */
        y = y % 900;    /*берем остаток от деления на 900 чтобы объект появлялся в доступном для пользователся месте*/
        target.setPosition(x, y); /*устанавливаем объект на координатах х у*/
        if (goodClicks % 5 == 0) { /*если количество попаданий кратно 5 то уменьшаем размер объекта на 3 пикселя*/
            size = size - 3;
        }
        target.setSize(sf::Vector2f(size, size)); /* задаем объекту размер*/

    }

/**
 * функция для подсчета общих кликов и попаданий по объекту
 * @param position - переменная, в котороой хранятся координаты курсора во время нажатия клавиши
 */
    void leftClick(Vector2i position) {
        if (target.getGlobalBounds().contains(position.x,
                                              position.y)) { /*если попали по объекту то рисуем новый объект вызывая функцию newrect*/
            newrect();
            goodClicks++; /*увеличиваем кол-во попаданий на 1*/
            timer.restart(); /*запускаем занаво таймер*/
        }
        totalClicks++; /*увеличиваем кол-во общих попаданий на 1*/
        txt.setString(std::to_string(goodClicks) + "/" + /*выводим строку "количеством попаданий/кол-во нажатий" */
                      std::to_string(totalClicks));
    }

    bool end() const {
        return timer.getElapsedTime().asSeconds() > 5;
    } /*булево поле end которое является результатом сравнения времени от нажатия с 5 секундами  */
};

#ifndef KLICKER_STRUCT_H
#define KLICKER_STRUCT_H

#endif //KLICKER_STRUCT_H
