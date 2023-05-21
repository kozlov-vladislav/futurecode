
## Терминология

## Окна

`sf::Window` и `sf::RenderWindow` являются классами в SFML, предназначенными для создания окон приложения.

`sf::Window` - это базовый класс для создания окна, который предоставляет минимальный набор функций для работы с окном, таких как создание, закрытие и получение размера окна. Однако, он не предоставляет функциональности для отрисовки графики.

`sf::RenderWindow` - это класс, который наследует все функции `sf::Window`, но также предоставляет возможность отрисовки графики в окне. Он содержит методы для отображения графических объектов, таких как спрайты, текстуры и т.д.

Таким образом, основное отличие между `sf::Window` и `sf::RenderWindow` заключается в том, что `sf::Window` предоставляет только базовые функции для работы с окном, а `sf::RenderWindow` дополнительно предоставляет функциональность для отрисовки графики. Если вам не нужно отображать графику в окне, то можно использовать `sf::Window`. Если же вы планируете отображать графику, то следует использовать `sf::RenderWindow`.

## Ивенты

События (events) в SFML - это события, которые происходят в окне приложения, такие как нажатия клавиш, движения мыши, изменения размера окна и т.д. В SFML события обрабатываются через цикл обработки событий (event loop).

Цикл обработки событий начинается с вызова функции `pollEvent()` у объекта окна. Эта функция проверяет, произошло ли какое-либо событие, и если да, то возвращает его в виде объекта `Event`. Затем мы можем проверить тип события и выполнить соответствующие действия.

Например, если мы хотим обработать нажатие клавиши, мы можем проверить, что тип события равен `sf::Event::KeyPressed`, а затем проверить код клавиши, используя поле `event.key.code`.

В цикле обработки событий мы также можем обновлять состояние нашего приложения в зависимости от произошедших событий. Например, если мы обрабатываем движение мыши, мы можем изменить положение объекта на экране в соответствии с новым положением мыши.

Цикл обработки событий продолжается до тех пор, пока окно не будет закрыто или пока мы не прервем цикл вручную.

## Текст

`sf::Text` в SFML представляет собой класс для отображения текста на экране. Он позволяет задавать шрифт, размер, цвет и позицию текста, а также содержит методы для изменения содержимого текста и выравнивания.

Для работы с `sf::Text` необходимо загрузить шрифт с помощью класса `sf::Font`, после чего можно создать объект `sf::Text` и задать ему параметры. Для отображения текста на экране необходимо вызвать метод `draw()` у объекта класса `sf::RenderWindow`.

## Текстуры

`sf::RenderTexture` в SFML представляет собой текстуру, на которую можно рисовать графические объекты, используя все возможности класса `sf::RenderWindow`. Она позволяет создавать сложные изображения, которые могут быть сохранены в файл или использованы в качестве текстуры для других объектов.

Для работы с `sf::RenderTexture` необходимо создать объект класса `sf::RenderTexture`, задать ему размер и начать рисование с помощью метода `clear()`. Затем можно нарисовать нужные объекты, используя методы класса `sf::RenderWindow`. После завершения рисования необходимо вызвать метод `display()` и получить текстуру с помощью метода `getTexture()`.

`sf::Sprite` в SFML представляет собой объект, который может быть отображен на экране и содержит текстуру. Он может быть использован для отображения изображений, анимации, игровых объектов и т.д.

Для работы с `sf::Sprite` необходимо создать объект класса `sf::Sprite`, задать ему текстуру и, при необходимости, установить его позицию, масштаб и поворот. Затем можно отобразить спрайт на экране с помощью метода `draw()` класса `sf::RenderWindow`.

## Пример Создание окна1

```c++
#include <SFML/Graphics.hpp>
int main()
{
	sf::Window window(
		sf::VideoMode(640, 480),
		"Hello World");
	return 0;
}

```

## Пример Создание окна2

```c++
#include <SFML/Graphics.hpp>
int main()
{
	sf::Window window(
		sf::VideoMode(640, 480),
		"Hello World");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type ==
			sf::Event::Closed)
				window.close();
	}
}

```

## Пример Окно и статическая фигура

```c++
#include <SFML/Graphics.hpp>
int main()
{
	sf::RenderWindow window(
		sf::VideoMode(640, 480),
		"Hello World");
	sf::CircleShape shape(200);

	while (window.isOpen())
	{
		sf::Event event;
		while (
			window.pollEvent(event))
			if (event.type ==
			sf::Event::Closed)
				window.close();

		window.clear();
		window.draw(shape);
		window.display();
	}
}
```

## Пример Капли дождя

```c++
#include <SFML/Graphics.hpp>
#include <cstdlib>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rain Circles");

    // Create an array of circles
    const int numCircles = 100;
    sf::CircleShape circles[numCircles];

    // Initialize the circles with random positions and sizes
    for (int i = 0; i < numCircles; i++)
    {
        circles[i].setRadius(std::rand() % 10 + 5); // Random radius between 5 and 14
        circles[i].setPosition(std::rand() % 800, std::rand() % 600); // Random position within the window
        circles[i].setFillColor(sf::Color(255, 255, 255, std::rand() % 128 + 128)); // Random semi-transparent white color
    }

    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Move the circles down by a random amount
        for (int i = 0; i < numCircles; i++)
        {
            circles[i].move(0, 0.05*(std::rand() % 5 + 1)); // Random vertical movement between 1 and 5 pixels
            if (circles[i].getPosition().y > 600) // If circle goes below the window, reset its position to the top
            {
                circles[i].setPosition(std::rand() % 800, std::rand() % 50 - 100);
            }
        }

        // Clear the window and draw the circles
        window.clear(sf::Color(0, 0, 0));
        for (int i = 0; i < numCircles; i++)
        {
            window.draw(circles[i]);
        }
        window.display();
    }
}
```


## Пример Синусоида

```c++
#include <SFML/Graphics.hpp>
#include <cmath>

const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Function Plotter");

    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(0, HEIGHT / 2);
    xAxis[1].position = sf::Vector2f(WIDTH, HEIGHT / 2);
    xAxis[0].color = sf::Color::White;
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(WIDTH / 2, 0);
    yAxis[1].position = sf::Vector2f(WIDTH / 2, HEIGHT);
    yAxis[0].color = sf::Color::White;
    yAxis[1].color = sf::Color::White;

    sf::VertexArray plot(sf::LinesStrip);

    float xMin = -10;
    float xMax = 10;
    float xStep = 0.1;

    for (float x = xMin; x <= xMax; x += xStep)
    {
        float y = sin(x); // Replace with user input function

        float xPos = (x - xMin) / (xMax - xMin) * WIDTH;
        float yPos = (1 - (y + 1) / 2) * HEIGHT;

        plot.append(sf::Vertex(sf::Vector2f(xPos, yPos), sf::Color::Green));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.draw(xAxis);
        window.draw(yAxis);
        window.draw(plot);

        window.display();
    }
}
```

## Пример Отрисовка многочлена

```c++
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Quadratic Equation Solver");

    // Define constants for quadratic equation
    const double a = 1;
    const double b = 2;
    const double c = -3;

    // Calculate discriminant
    double discriminant = b * b - 4 * a * c;

    // Calculate roots of quadratic equation
    double x1 = (-b + std::sqrt(discriminant)) / (2 * a);
    double x2 = (-b - std::sqrt(discriminant)) / (2 * a);

    std::cout << "x1 = " << x1 << ", x2 = " << x2 << std::endl;

    // Define axes and points for plotting
    sf::VertexArray x_axis(sf::Lines, 2);
    x_axis[0].position = sf::Vector2f(0, 300);
    x_axis[1].position = sf::Vector2f(800, 300);
    x_axis[0].color = sf::Color::Black;
    x_axis[1].color = sf::Color::Black;

    sf::VertexArray y_axis(sf::Lines, 2);
    y_axis[0].position = sf::Vector2f(400, 0);
    y_axis[1].position = sf::Vector2f(400, 600);
    y_axis[0].color = sf::Color::Black;
    y_axis[1].color = sf::Color::Black;

    sf::VertexArray quadratic(sf::LineStrip, 200);
    for (int i = 0; i < 200; i++)
    {
        double x = i - 100;
        double y = a * x * x + b * x + c;
        quadratic[i].position = sf::Vector2f(x + 400, -y + 300);
        quadratic[i].color = sf::Color::Red;
    }

    // Draw axes and quadratic
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(x_axis);
        window.draw(y_axis);
        window.draw(quadratic);
        window.display();
    }
}
```


## Пример Поле ввода

```c++
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Text Input");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Error loading font." << std::endl;
        return 1;
    }
    sf::Text text("", font, 24);
    text.setFillColor(sf::Color::Black);
    sf::RectangleShape inputBox(sf::Vector2f(400.f, 50.f));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineThickness(2.f);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setPosition(200.f, 275.f);
    text.setPosition(inputBox.getPosition() + sf::Vector2f(10.f, 10.f)); // set text position inside input box
    bool isTyping = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (isTyping)
                {
                    if (event.text.unicode == '\b' && !text.getString().isEmpty())
                    {
                        text.setString(text.getString().substring(0, text.getString().getSize() - 1));
                    }
                    else if (event.text.unicode == '\r')
                    {
                        std::cout << "Submitted text: " << text.getString().toAnsiString() << std::endl;
                        text.setString("");
                        isTyping = false;
                    }
                    else if (event.text.unicode < 128)
                    {
                        text.setString(text.getString() + static_cast<char>(event.text.unicode));
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (inputBox.getGlobalBounds().contains(mousePos))
                    {
                        isTyping = true;
                    }
                    else
                    {
                        isTyping = false;
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(inputBox);
        window.draw(text);
        window.display();
    }
}
```

## Пример Карандаш

```c++
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Drawing App");
    sf::RenderTexture canvas;
    canvas.create(window.getSize().x, window.getSize().y);
    canvas.clear(sf::Color::White);
    sf::Sprite sprite(canvas.getTexture());
    sf::CircleShape brush(5.f);
    brush.setFillColor(sf::Color::Black);
    bool isDrawing = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                isDrawing = true;
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                isDrawing = false;
            }
            else if (event.type == sf::Event::MouseMoved && isDrawing)
            {
                brush.setPosition(sf::Vector2f(event.mouseMove.x, window.getSize().y - event.mouseMove.y));
                canvas.draw(brush);
                sprite.setTexture(canvas.getTexture(), true);
            }
        }
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }
}
```