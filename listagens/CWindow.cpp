#include "CWindow.hpp"
CWindow::CWindow(int _width, int _height) {
	height = _height; width = _width;
	simulation.resetSize(width, height);
    font.loadFromFile("arial.ttf");
    recSize.x = 101;
    recSize.y = 101;

    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);

    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 450, 600, TRUE);
}

void CWindow::Run() {
	bool isDrawing = false;
    int contador = 0;
    double maxTemp, minTemp;

	sf::Vector2f lastPos;

	sf::RectangleShape brush(recSize);
    sf::RectangleShape pixelPaint(sf::Vector2f(1, 1));

    sf::RenderWindow window(sf::VideoMode(width*2+ distance_of_draws, height*2+ distance_of_draws), L"Paint", sf::Style::Default);

    window.setPosition(sf::Vector2i(700, 300));
    //window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(100);


    canvas.create(width*2+distance_of_draws, height*2+ distance_of_draws);
    canvas.clear(sf::Color::White);

    sprite.setTexture(canvas.getTexture(), true);

	brush.setFillColor(sf::Color(255, 255, 0, 255));

    printMenu(recSize); paint_menu(); paint_menu();
    paint_design();
    paint_shortcuts();
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
                    printMenu(recSize); paint_menu(); paint_menu();
                    break;
                case sf::Keyboard::T:
                    std::cout << "Digite a nova temperatura: ";
                    double temperature;
                    std::cin >> temperature;
                    simulation.set_ActualTemperature(temperature);
                    brush.setFillColor(getRGB(temperature));
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::PageUp:
                    brush.setFillColor(sf::Color(255, 0, 0, 255));
                    simulation.set_ActualTemperature(simulation.getTmax());
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::PageDown:
                    brush.setFillColor(sf::Color(255, 255, 0, 255));
                    simulation.set_ActualTemperature(simulation.getTmin());
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::Up:
                    currentGrid++;
                    if (currentGrid > 3)currentGrid = 3;
                    paint_results();
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::Down:
                    currentGrid--;
                    if (currentGrid < 0)currentGrid = 0;
                    paint_results();
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::LShift:
                    recSize = case_LShift(recSize);
                    brush.setSize(recSize);
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::LControl:
                    recSize = case_LCtrl(recSize);
                    brush.setSize(recSize);
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::Comma:
                    simulation.minusDelta_t();
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::Period:
                    simulation.plusDelta_t();
                    printMenu(recSize); paint_menu();
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
                case sf::Keyboard::V:
                    simulation.changeMaterialPropertiesStatus();
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::G:
                    simulation.changeParallel();
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::S:
                    simulation.saveGrid("teste.txt");
                    break;
                case sf::Keyboard::A:
                    simulation.openGrid("teste.txt");
                    paint_results();
                    break;
                case sf::Keyboard::F:
                    isSourceActive = isSourceActive ? false : true;
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::E:
                    simulation.changeRightMaterial();
                    printMenu(recSize); paint_menu();
                    break;
                case sf::Keyboard::Q:
                    simulation.changeLeftMaterial();
                    printMenu(recSize); paint_menu();
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
                    simulation.grid[currentGrid]->draw(lastPos, recSize, simulation.get_ActualTemperature(), isSourceActive, simulation.getActualMaterial());

                    paint_results();
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                    isDrawing = false;
                break;
			} // switch event type
		}// while pollEvent

        if (runningSimulator && contador >= -1) {

            double start_time = std::time(0);

            if (simulation.getParallel() == 0) {
                simulation.run_otimization();
            }
            else if (simulation.getParallel()==1) {
                omp_set_num_threads(simulation.getNGRIDS());
                #pragma omp parallel
                {
                    simulation.run(omp_get_thread_num());
                }
            }
            else {
                simulation.run();
            }
            paint_results();
            contador = -1;
            std::cout << "Time: " << std::setw(5) << simulation.get_time() << " - duracao: " << std::time(0) - start_time << " seg       " << "\r";
            simulation.updateActualTime();
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

void CWindow::paint_results() {
    sf::RectangleShape pixelPaint(sf::Vector2f(1, 1));
    for (int i = 0; i < width; i++) {
        for (int k = 0; k < height; k++) {
            if (!simulation.grid[currentGrid]->operator()(i, k)->active)
                pixelPaint.setFillColor(sf::Color::White);
            else
                pixelPaint.setFillColor(getRGB(simulation.grid[currentGrid]->operator()(i, k)->temp));
            pixelPaint.setPosition(sf::Vector2f(i, k));
            canvas.draw(pixelPaint);
        }
    }
    for (int i = 0; i < width; i++) {
        for (int k = 0; k < height; k++) {
            if (!simulation.grid[currentGrid]->operator()(i, k)->active)
                pixelPaint.setFillColor(sf::Color::White);
            else
                pixelPaint.setFillColor(simulation.grid[currentGrid]->operator()(i, k)->material->getColor());
            pixelPaint.setPosition(sf::Vector2f(i+width+ distance_of_draws, k));
            canvas.draw(pixelPaint);
        }
    }

    canvas.display();
    paintStudyPoint();
}

void CWindow::paint_design() {
    sf::RectangleShape delimiter(sf::Vector2f(2, height));
    delimiter.setFillColor(sf::Color::Black);
    delimiter.setPosition(sf::Vector2f(width, 0));
    canvas.draw(delimiter);
    delimiter.setPosition(sf::Vector2f(width + distance_of_draws - 2, 0));
    canvas.draw(delimiter);
    delimiter.setSize(sf::Vector2f(width * 2 + distance_of_draws, 2));
    delimiter.setPosition(sf::Vector2f(0, 0));
    canvas.draw(delimiter);
    delimiter.setPosition(sf::Vector2f(0, height));
    canvas.draw(delimiter);
    delimiter.setPosition(sf::Vector2f(0, height + distance_of_draws));
    canvas.draw(delimiter);
}

void CWindow::paint_shortcuts() {
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);

    text.setString("######  Atalhos ######");
    text.move(sf::Vector2f(5, height + distance_of_draws + 2));
    canvas.draw(text);

    int y;
    y = draw_text("  O    - set observer point", 5, height + distance_of_draws + 2+20);
    y = draw_text("  R    - plot observer point", 5, y);
    y = draw_text("  C    - clear screen", 5, y);
    y = draw_text("  T    - choose temperature", 5, y);
    y = draw_text("PG UP  - temperature -> "+ std::to_string(simulation.getTmax()) + "K", 5, y);
    y = draw_text("PG DN  - temperature -> "+ std::to_string(simulation.getTmin()) + "K", 5, y);
    y = draw_text("LSHIFT - increase rectangle size", 5, y);
    y = draw_text("LCTRL  - decrease rectangle size", 5, y);
    y = draw_text("  >    - increase time delta", 5, y);
    y = draw_text("  <    - decrease time delta", 5, y);
    y = draw_text("  F    - temperature source", 5, y);
    y = draw_text("  G    - change parallelism", 5, y);
    y = draw_text("  E    - next material", 5, y);
    y = draw_text("  Q    - last material", 5, y);
    y = draw_text("  V    - variable material properties", 5, y);

    canvas.display();
}
void CWindow::paint_menu() {
    /// clear menu
    sf::RectangleShape delimiter(sf::Vector2f(width, height));
    delimiter.setFillColor(sf::Color::White);
    delimiter.setPosition(sf::Vector2f(width+distance_of_draws, height+distance_of_draws+2));
    canvas.draw(delimiter);

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);
    int x = width + distance_of_draws + 10;
    text.setString("######  Menu ######");
    text.move(sf::Vector2f(x, height + distance_of_draws + 2));
    canvas.draw(text);

    int y;
    y = draw_text("Temperatura atual: " + std::to_string(simulation.get_ActualTemperature()) + "K", x, height + distance_of_draws + 2 + 20);

    y = draw_text("Intervalos de tempo (dt): " + std::to_string(simulation.get_delta_t()) + " s", x, y);
     y = draw_text("Rectangle size (x,y): " + std::to_string(recSize.x * 0.026) + "," + std::to_string(recSize.y * 0.026) + " cm", x, y);
     std::string _temp_text = (runningSimulator ? "running" : "stoped");
     y = draw_text("Status: " + _temp_text, x, y);
     _temp_text = (isSourceActive ? "yes" : "no");
     y = draw_text("Source: " + _temp_text, x, y);
     y = draw_text("Perfil: " + std::to_string(currentGrid), x, y);
     y = draw_text("Paralellism: " + std::to_string(simulation.getParallel()), x, y);
     y = draw_text("Material: " + simulation.getActualMaterial(), x, y);
     (simulation.getMaterialStatus() ? "yes" : "no");
     y = draw_text("Propriedades variando: " +_temp_text, x, y);

    canvas.display();
}

int CWindow::draw_text(std::string _text, int start_x, int start_y) {
    sf::Text text;
    int character_size = 15;
    text.setCharacterSize(character_size);
    text.setFont(font);
    text.setFillColor(sf::Color::Black);

    text.move(sf::Vector2f(start_x, start_y));
    text.setString(_text);
    canvas.draw(text);
    return start_y + character_size + 2;
}

void CWindow::paintStudyPoint() {
    if (currentGrid == simulation.getStudyGrid()) {
        sf::RectangleShape pixelPaint(sf::Vector2f(3, 3));
        pixelPaint.setFillColor(sf::Color::Black);
        pixelPaint.setPosition(simulation.getPositionStudyVector());
        canvas.draw(pixelPaint);
        canvas.display();
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
    std::cout << "Paralellism: " << simulation.getParallel() << std::endl;
    std::cout << "Material: " << simulation.getActualMaterial() << std::endl;
    std::cout << "Propriedades variando: " << (simulation.getMaterialStatus() ? "yes" : "no") << std::endl;
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
    std::cout << "  F    - temperature source" << std::endl;
    std::cout << "  G    - change parallelism" << std::endl;
    std::cout << "  E    - next material" << std::endl;
    std::cout << "  Q    - last material" << std::endl;
    std::cout << "  V    - variable material properties" << std::endl;
    std::cout << "---------------------------------" << std::endl;
}