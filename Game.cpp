#include "Game.h"

int columnUserInput = -1;
int rowUserInput = -1;

std::condition_variable cv;

void enterCoordinates() {
    std::cin >> columnUserInput >> rowUserInput;
    cv.notify_one();
}

std::string Game::getCenteredText(const std::string& text, int width) {
    int spaces = width - (int)text.length();
    int left = spaces / 2;
    int right = spaces - left;
    return std::string(left, ' ') + text + std::string(right, ' ');
}

std::string Game::getCenteredTitle(const std::string &text, int width) {
    int spaces = width - (int)text.length();
    int left = spaces / 2 - 1;
    int right = spaces - left - 1;
    std::string result = std::string(left, '=') + ' ' + text + ' ' + std::string(right, '=');
    return result.substr(0, width);
}

bool Game::isAWinner(char playerSymbol, bool isVerticalCheck) {
    if (isVerticalCheck) {
        std::vector<std::vector<bool>> visited(this->tableSize, std::vector<bool>(this->tableSize, false));
        std::vector<std::pair<int, int>> queue;
        for (int i = 0; i < this->tableSize; i++) {
            if (this->table[0][i] == playerSymbol) {
                queue.emplace_back(0, i);
                visited[0][i] = true;
            }
        }
        while (!queue.empty()) {
            std::pair<int, int> current = queue.back();
            queue.pop_back();
            if (current.first == this->tableSize - 1) {
                return true;
            }
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) {
                        continue;
                    }
                    int x = current.first + i;
                    int y = current.second + j;
                    if (x >= 0 && x < this->tableSize && y >= 0 && y < this->tableSize && !visited[x][y] && this->table[x][y] == playerSymbol) {
                        queue.emplace_back(x, y);
                        visited[x][y] = true;
                    }
                }
            }
        }
        return false;
    } else {
        std::vector<std::vector<bool>> visited(this->tableSize, std::vector<bool>(this->tableSize, false));
        std::vector<std::pair<int, int>> queue;
        for (int i = 0; i < this->tableSize; i++) {
            if (this->table[i][0] == playerSymbol) {
                queue.emplace_back(i, 0);
                visited[i][0] = true;
            }
        }
        while (!queue.empty()) {
            std::pair<int, int> current = queue.back();
            queue.pop_back();
            if (current.second == this->tableSize - 1) {
                return true;
            }
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) {
                        continue;
                    }
                    int x = current.first + i;
                    int y = current.second + j;
                    if (x >= 0 && x < this->tableSize && y >= 0 && y < this->tableSize && !visited[x][y] && this->table[x][y] == playerSymbol) {
                        queue.emplace_back(x, y);
                        visited[x][y] = true;
                    }
                }
            }
        }
        return false;
    }
}

void Game::printTable() {
    std::cout << this->getCenteredTitle("TABLERO", (this->tableSize == 7) ? 25 : 37) << std::endl;
    if (this->tableSize == 7) {
        std::cout << "J  ";
    } else {
        std::cout << "   ";
    }
    std::cout << this->getCenteredText("JUGADOR 2", 2 * this->tableSize - 1);
    if (this->tableSize == 7) {
        std::cout << std::setw(this->tableSize - 1) << " ";
        std::cout << "  J" << std::endl;
    } else {
        std::cout << std::endl;
    }
    std::string player17x7 = "UGADOR ";
    std::string player111x11 = " JUGADOR 1 ";
    for (int i = 0; i < tableSize; i++) {
        if (this->tableSize == 7) {
            std::cout << player17x7[i] << "  ";
        } else {
            std::cout << player111x11[i] << "  ";
        }

        std::cout << std::setw(i + 1);
        for (int j = 0; j < tableSize; j++) {
            std::cout << table[i][j] << " ";
        }

        if (this->tableSize == 7) {
            std::cout << std::setw(this->tableSize - (i + 1)) << "";
            std::cout << " " << player17x7[i];
        } else {
            std::cout << std::setw(this->tableSize - (i + 1)) << "";
            std::cout << " " << player111x11[i];
        }
        std::cout << std::endl;
    }
    if (this->tableSize == 7) {
        std::cout << "1  ";
    } else {
        std::cout << "   ";
    }
    std::cout << std::setw(this->tableSize - 1) << " ";
    std::cout << this->getCenteredText("JUGADOR 2", 2 * this->tableSize - 1);
    if (this->tableSize == 7) {
        std::cout << "  1" << std::endl;
    } else {
        std::cout << std::endl;
    }
}

Game::Game() {
    this->tableSize = 0;
    this->indexOfWinnerPlayer = -1;
    this->turnTime = 0;
}

void Game::setUpGame() {
    system("cls");
    std::cout << "***      ***  ************  ***      ***" << std::endl;
    std::cout << "***      ***  ************   ***    *** " << std::endl;
    std::cout << "***      ***  ***             ***  ***  " << std::endl;
    std::cout << "***      ***  ***              ******   " << std::endl;
    std::cout << "************  ************      ****    " << std::endl;
    std::cout << "************  ************      ****    " << std::endl;
    std::cout << "***      ***  ***              ******   " << std::endl;
    std::cout << "***      ***  ***             ***  ***  " << std::endl;
    std::cout << "***      ***  ************   ***    *** " << std::endl;
    std::cout << "***      ***  ************  ***      ***" << std::endl;
    std::cout << std::endl << "Ingrese la cantidad de celdas del tablero (7-11): ";
    std::cin >> this->tableSize;
    while (!(this->tableSize == 7 || this->tableSize == 11)) {
        std::cout << "Ingrese la cantidad de celdas del tablero (7-11): ";
        std::cin >> this->tableSize;
    }
    this->table = std::vector<std::vector<char>>(tableSize, std::vector<char>(tableSize, 'x'));
    std::cout << std::endl << "Ingrese el tiempo por turno (en segundos): ";
    std::cin >> this->turnTime;
    system("cls");
}

void Game::setUpPlayers() {
    int numberOfPlayers;
    std::cout << "Cuantos jugadores van a jugar? (1-2): ";
    std::cin >> numberOfPlayers;
    if (numberOfPlayers == 1) {
        std::string name;
        std::cout << "Cual es tu nombre?: ";
        std::cin >> name;
        Player player1(name, 'R', false, this->turnTime);
        Player player2("Computadora", 'A', true, this->turnTime);
        this->players.push_back(player1);
        this->players.push_back(player2);
    } else {
        std::string name1, name2;
        std::cout << "Cual es el nombre del primer jugador?: ";
        std::cin >> name1;
        std::cout << "Cual es el nombre del segundo jugador?: ";
        std::cin >> name2;
        Player player1(name1, 'R', false, this->turnTime);
        Player player2(name2, 'A', false, this->turnTime);
        this->players.push_back(player1);
        this->players.push_back(player2);
    }
    system("cls");
}

void Game::startGame() {
    srand(time(nullptr));
    int turn = 0;
    while(true) {
        this->printTable();
        std::cout << std::endl << "Turno de " << this->players[turn].getName() << " (Jugador " << turn + 1 << " - " << this->players[turn].getPlayerSymbol() << ")" << std::endl;
        if (this->players[turn].isIsComputer()) {
            std::cout << "La computadora esta pensando..." << std::endl;
            Sleep(1000);
            int x, y;
            do {
                x = rand() % this->tableSize;
                y = rand() % this->tableSize;
            } while (this->table[x][y] != 'x');
            this->table[x][y] = this->players[turn].getPlayerSymbol();
        } else {
            this->players[turn].setTimeLeft(this->turnTime);
            std::cout << "Te quedan " << this->players[turn].getTimeLeft() << " segundos para ingresar las coordenadas" << std::endl;
            std::cout << "Ingrese las coordenadas de la celda a marcar (x y): ";
            std::thread th(enterCoordinates);
            std::mutex mtx;
            std::unique_lock<std::mutex> lck(mtx);
            int timeLeftInterval = this->players[turn].getTimeLeft() < 3 ? this->players[turn].getTimeLeft() : 3;
            while (cv.wait_for(lck, std::chrono::seconds(timeLeftInterval)) == std::cv_status::timeout) {
                this->players[turn].decreaseTimeLeft(timeLeftInterval);
                if (this->players[turn].getTimeLeft() <= 0) {
                    std::cout << std::endl << "Se te acabo el tiempo!" << std::endl;
                    break;
                }
                system("cls");
                this->printTable();
                std::cout << std::endl << "Turno de " << this->players[turn].getName() << " (Jugador " << turn + 1 << " - " << this->players[turn].getPlayerSymbol() << ")" << std::endl;
                std::cout << "Te quedan " << this->players[turn].getTimeLeft() << " segundos para ingresar las coordenadas" << std::endl;
                std::cout << "Ingrese las coordenadas de la celda a marcar (x y): ";
                timeLeftInterval = this->players[turn].getTimeLeft() < 3 ? this->players[turn].getTimeLeft() : 3;
            }
            th.join();
            if (!(columnUserInput < 0 || columnUserInput >= this->tableSize || rowUserInput < 0 || rowUserInput >= this->tableSize)) {
                if (this->table[columnUserInput][rowUserInput] == 'x') {
                    if (this->players[turn].getTimeLeft() > 0) {
                        this->table[columnUserInput][rowUserInput] = this->players[turn].getPlayerSymbol();
                    }
                }
            }
        }
        if (isAWinner(this->players[turn].getPlayerSymbol(), turn % 2)) {
            this->printTable();
            system("cls");
            break;
        }
        turn = (turn + 1) % 2;
        system("cls");
    }
    this->indexOfWinnerPlayer = turn;
}

Game::~Game() {
    this->printTable();
    if (this->players[this->indexOfWinnerPlayer].isIsComputer()) {
        std::cout << std::endl << "La computadora ha ganado!" << std::endl;
    } else {
        std::cout << std::endl << "El jugador " << this->players[this->indexOfWinnerPlayer].getName() << " (Jugador " << this->indexOfWinnerPlayer + 1 << " - " << this->players[this->indexOfWinnerPlayer].getPlayerSymbol() << ")" << " ha ganado!" << std::endl;
    }
    std::cout << std::endl << this->getCenteredTitle("JUEGO TERMINADO", (this->tableSize == 7) ? 25 : 37) << std::endl;
}
