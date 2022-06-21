#include <iostream>
#include "tst/struct.h"

using namespace sf;


/**
 * функция для создания меню в которой находится создание и отрисовка эллементов меню
 * @param window
 * @return 1 если не установили иконку и 0 если все хорошо
 */
int menu(RenderWindow &window) {
    Texture menuTexture1, menuTexture2, aboutText, menuExit; /* создаем текстуры*/
    menuTexture1.loadFromFile("graphics/start.png");
    menuTexture2.loadFromFile("graphics/menu_about.png");
    aboutText.loadFromFile("graphics/about.png");
    menuExit.loadFromFile("graphics/exit.png");
    Sprite start(menuTexture1), menu_about(menuTexture2), about(aboutText), exit(
            menuExit);  /*теперь создаем спрайты из текстур */
    bool isMenu = true; /* булевая переменная отвечающая за состояние меню, по дефолту 1, чтобы при открытии окна показывалось меню */
    int menuNum; /* переменная отвечающая за то, что отображать */
    start.setPosition(660, 120); /* выдаем позиции спрайтам в меню */
    menu_about.setPosition(660, 340);
    exit.setPosition(660, 560);
    auto image = sf::Image{}; /*устанавливаем иконку программы */
    if (!image.loadFromFile("graphics/aimlab.png")) { /*устанавливаем иконку приложения*/
        return 1;
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());


    while (isMenu) {/*пока isMenu = 1 отображаем меню */
        Event event;
        while (window.pollEvent(event)) /*опрашиваем очередь событий*/
            if (event.type == sf::Event::Closed) {
                window.close();
                isMenu = false;
            }
        start.setColor(Color::White);/*закрашываем спрайты белым */
        menu_about.setColor(Color::White);
        exit.setColor(Color::White);
        menuNum = 0;
        window.clear(Color(5, 0, 172)); /*закрашиваем фон меню */
        if (IntRect(660, 120, 600, 200).contains(Mouse::getPosition(window))) {
            start.setColor(Color::Blue);
            /*при попадании курсора в область указанных координат она окрашивается в синий */
            menuNum = 1;
            /*при попадании курсора в область указанных координат полю menuNum присваивается значение 1*/
        }
        if (IntRect(660, 340, 600, 200).contains(Mouse::getPosition(window))) {
            menu_about.setColor(Color::Blue);
            menuNum = 2;
        }
        if (IntRect(660, 560, 600, 200).contains(Mouse::getPosition(window))) {
            exit.setColor(Color::Blue);
            menuNum = 3;
        }

        window.draw(start);
        window.draw(menu_about);
        window.draw(exit);

        window.display();
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (menuNum == 1)
                isMenu = false; /*если поле menuNum = 1, то полю isMenu присваивается значение false -->цикл закрывается и дальше идет выполение кода в фукции main */
            if (menuNum ==
                2) {  /*если поле menuNum = 2, то у нас начинается отрисоква информационного табло, оно будет отображаться пока не нажата клавиша escape*/
                about.setPosition(410, 340);
                window.clear(Color::Blue);
                window.draw(about);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape)); /*при нажатии escape выходим из вкладки "о проекте"*/
            }
            if (menuNum == 3) {   /*если нажать кнопку с надписью exit, то программа закроется*/
                window.close();
                isMenu = false;
            }


        }
    }


}

/**
 * основная функция в которой происходит отрисовка окна и вызов следующих функций: menu, leftClick
 * @return создает окно в котором отображается сначала меню, потом происходит вызов функций которые создают игру
 */
int main() {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "aimlab"); /*создаем окно 1920*1080*/
    menu(window); /*вызываем функцию menu */
    Music music; /*создаем поле music*/

    auto image = sf::Image{}; /*устанавливаем иконку программы */
    if (!image.loadFromFile("graphics/aimlab.png")) {
        return 1;
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    music.openFromFile("audio/ost.wav"); /*сохраняем в поле music файл с музыкой*/
    music.play(); /*проигрываем музыку*/
    music.setVolume(5); /*устанавливаем громкость музыки*/
    music.setLoop(true); /*зацикливаем музыку*/
    Game game;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type ==
                sf::Event::MouseButtonPressed) { /*если мы нажали левую кнопку мыши, то передаем позицию курсора в leftClick*/
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    auto position = sf::Mouse::getPosition(window);
                    game.leftClick(position);
                }
            }
        }
        if (game.end()) { /*если end == true, то закрываем окно*/
            window.close();
        }
        game.draw(window);
        window.display();
    }
    return 0;

}
