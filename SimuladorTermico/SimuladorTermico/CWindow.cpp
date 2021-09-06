#include "CWindow.hpp"
CWindow::CWindow(int _width, int _height) {
	height = _height; width = _width;
	simulation.resetSize(width, height);

    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);

    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 430, 450, TRUE);
}

void CWindow::Run() {
	bool isDrawing = false;
    int contador = 0;
    double maxTemp, minTemp;

	sf::Vector2f lastPos;
    sf::Vector2f recSize(15, 15);

	sf::RectangleShape brush(recSize);
    sf::RectangleShape pixelPaint(sf::Vector2f(1, 1));

    sf::RenderWindow window(sf::VideoMode(width, height), L"Simulador de difusividade termica", sf::Style::Default);

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(100);

    canvas.create(width, height);
    canvas.clear(sf::Color::White);

    sprite.setTexture(canvas.getTexture(), true);

	brush.setFillColor(sf::Color(255, 255, 0, 255));

    printMenu(recSize);
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::C:
                    canvas.clear(sf::Color::White);
                    simulation.resetGrid();
                    canvas.display();
                    break;
                case sf::Keyboard::P:
                    runningSimulator = runningSimulator ? false : true;
                    printMenu(recSize);
                    break;
                case sf::Keyboard::T:
                    std::cout << "Digite a nova temperatura: ";
                    double temperature;
                    std::cin >> temperature;
                    simulation.set_ActualTemperature(temperature);
                    brush.setFillColor(getRGB(temperature));
                    printMenu(recSize);
                    break;
                case sf::Keyboard::PageUp:
                    brush.setFillColor(sf::Color (255, 0, 0, 255));
                    simulation.set_ActualTemperature(simulation.getTmax());
                    printMenu(recSize);
                    break;
                case sf::Keyboard::PageDown:
                    brush.setFillColor(sf::Color(255, 255, 0, 255));
                    simulation.set_ActualTemperature(simulation.getTmin());
                    printMenu(recSize);
                    break;
                case sf::Keyboard::Up:
                    currentGrid++;
                    if (currentGrid > 3)currentGrid = 3;
                    paint();
                    printMenu(recSize);
                    break;
                case sf::Keyboard::Down:
                    currentGrid--;
                    if (currentGrid <0)currentGrid = 0;
                    paint();
                    printMenu(recSize);
                    break;
                case sf::Keyboard::LShift:
                    recSize = case_LShift(recSize);
                    brush.setSize(recSize);
                    printMenu(recSize);
                    break;
                case sf::Keyboard::LControl:
                    recSize = case_LCtrl(recSize);
                    brush.setSize(recSize);
                    printMenu(recSize);
                    break;
                case sf::Keyboard::Comma:
                    simulation.minusDelta_t();
                    printMenu(recSize);
                    break;
                case sf::Keyboard::Period:
                    simulation.plusDelta_t();
                    printMenu(recSize);
                    break;
                case sf::Keyboard::O:
                    studyCoordinates = sf::Mouse::getPosition(window);
                    simulation.studyPosition(studyCoordinates, currentGrid);
                    pixelPaint.setFillColor(sf::Color::Black);
                    pixelPaint.setPosition((sf::Vector2f)studyCoordinates);
                    canvas.draw(pixelPaint);
                    canvas.display();
                    break;
                case sf::Keyboard::R:
                    simulation.plot();
                    break;
                case sf::Keyboard::F:
                    isSourceActive = isSourceActive ? false : true;
                    printMenu(recSize);
                    break;
                }
            case sf::Event::Resized: {
                sf::View view(window.getView());
                const sf::Vector2f size(window.getSize().x, window.getSize().y);
                view.setSize(size);
                view.setCenter(size / 2.f);
                window.setView(view);
                break;
            }
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDrawing = true;
                    lastPos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                    simulation.grid[currentGrid]->draw(lastPos, recSize, simulation.get_ActualTemperature(), isSourceActive);

                    brush.setPosition(lastPos);
                    canvas.draw(brush);
                    canvas.display();
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                    isDrawing = false;
                break;
			} // switch event type
		}// while pollEvent
        
        if (runningSimulator && contador >= -1) {
            simulation.run();
            contador = -1;
            paint();
        }
        contador++;
        window.clear(sf::Color(64, 64, 64));
        window.draw(sprite);
        window.display();
	}// while is open
}

sf::Color CWindow::getRGB(double temp) {
    double maxTemp = simulation.getTmax();
    double minTemp = simulation.getTmin();
    int blue = 0;
    int n = (maxTemp - temp)*255/(maxTemp - minTemp);

    return sf::Color(255, n, 0, 255);
}

void CWindow::paint() {
    sf::RectangleShape pixelPaint(sf::Vector2f(1, 1));
    for (int i = 0; i < width; i++) {
        for (int k = 0; k < height; k++) {
            if (!simulation.grid[currentGrid]->operator()(i, k)->active)
                pixelPaint.setFillColor(sf::Color::White);
            else
                pixelPaint.setFillColor(getRGB(simulation.grid[currentGrid]->operator()(i, k)->temp));
            pixelPaint.setPosition(sf::Vector2f(i, k));
            canvas.draw(pixelPaint);
            canvas.display();
        }
    }
}

sf::Vector2f CWindow::case_LShift(sf::Vector2f recSize) {
    if (recSize.x < 120) {
        recSize.x += 2;
        recSize.y += 2;
    }
    return recSize;
}

sf::Vector2f CWindow::case_LCtrl(sf::Vector2f recSize) {
    if (recSize.x > 2) {
        recSize.x -= 2;
        recSize.y -= 2;
    }
    return recSize;
}

void CWindow::printStudy() {
    std::vector<double> temp = simulation.getTemperatureStudy();
    std::vector<double> time = simulation.getTimeStudy();

    std::cout << "time  - temp" << std::endl;
    for (int i = 0; i < temp.size(); i++)
        std::cout << time[i] << "  -  " << temp[i] << std::endl;
}

void CWindow::printMenu(sf::Vector2f recSize) {
    system("cls");
    std::cout << "---------------------------------" << std::endl;
    std::cout << "     Menu de configuracoes" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Temperatura atual: " << simulation.get_ActualTemperature() << "K" << std::endl;
    std::cout << "Intervalos de tempo (dt): " << simulation.get_delta_t() << " s" << std::endl;
    std::cout << "Rectangle size (x,y): " << recSize.x*0.026 << "," << recSize.y*0.026 <<" cm" << std::endl;
    std::cout << "Status: " << (runningSimulator ? "running" : "stoped") << std::endl;
    std::cout << "Source: " << (isSourceActive ? "yes" : "no") << std::endl;
    std::cout << "Perfil: " << currentGrid << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "  P    - PAUSE/RUN" << std::endl;
    std::cout << "  O    - set observer point" << std::endl;
    std::cout << "  R    - plot observer point" << std::endl;
    std::cout << "  C    - clear screen" << std::endl;
    std::cout << "  T    - choose temperature" << std::endl;
    std::cout << "PG UP  - temperature -> " << simulation.getTmax() << "K" << std::endl;
    std::cout << "PG DN  - temperature -> " << simulation.getTmin() << "K" << std::endl;
    std::cout << "LSHIFT - increase rectangle size" << std::endl;
    std::cout << "LCTRL  - decrease rectangle size" << std::endl;
    std::cout << "  >    - increase time delta" << std::endl;
    std::cout << "  <    - decrease time delta" << std::endl;
    std::cout << "---------------------------------" << std::endl;
}