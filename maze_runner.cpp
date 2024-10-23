#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>
#include <mutex>

// Representação do labirinto
using Maze = std::vector<std::vector<char>>;

// Estrutura para representar uma posição no labirinto
struct Position {
    int row;
    int col; 
};

// Variáveis globais
Maze maze;
int num_rows;
int num_cols;
std::stack<Position> valid_positions;

std::vector<std::thread> threads; // Para armazenar as threads criadas

std::mutex m;
// Função para carregar o labirinto de um arquivo
Position load_maze(const std::string& file_name) {
    // TODO: Implemente esta função seguindo estes passos:
    // 1. Abra o arquivo especificado por file_name usando std::ifstream
    std::ifstream arquivo(file_name);
    // 6. Trate possíveis erros (arquivo não encontrado, formato inválido, etc.)    
    if(!arquivo.is_open()){
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        return {-1, -1};
    }
    
    // 2. Leia o número de linhas e colunas do labirinto
    arquivo >> num_rows >> num_cols;
    // 3. Redimensione a matriz 'maze' de acordo (use maze.resize())
    maze.resize(num_rows, std::vector<char>(num_cols));
    // 4. Leia o conteúdo do labirinto do arquivo, caractere por caractere
    // 5. Encontre e retorne a posição inicial ('e')
    Position position = {-1, -1};
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            arquivo >> maze[i][j];
            if(maze[i][j] == 'e'){
                position.row = i;
                position.col = j;
            }
        }
    }
    // 7. Feche o arquivo após a leitura
     arquivo.close();
    
    return position; // Placeholder - substitua pelo valor correto
}

// Função para imprimir o labirinto
void print_maze() {
    //protocolo de entrada e saída
    // TODO: Implemente esta função
    // 1. Percorra a matriz 'maze' usando um loop aninhado
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            std::cout << maze[i][j]; // 2. Imprima cada caractere usando std::cout
        }
        std::cout << "\n"; // 3. Adicione uma quebra de linha (std::cout << '\n') ao final de cada linha do labirinto
    }
    std::cout << "\n";
    
}

// Função para verificar se uma posição é válida
bool is_valid_position(int row, int col) {
    // TODO: Implemente esta função
    // 1. Verifique se a posição está dentro dos limites do labirinto
    if(row >= 0 && row < num_rows && col >= 0 && col < num_cols){
        return maze[row][col] == 'x' || maze[row][col] == 's';
    }
    return false;
    // 2. Verifique se a posição é um caminho válido (maze[row][col] == 'x')
    // 3. Retorne true se ambas as condições forem verdadeiras, false caso contrário
    // Placeholder - substitua pela lógica correta
}

// Função principal para navegar pelo labirinto
bool walk(Position pos) {
    // TODO: Implemente a lógica de navegação aqui
    // 2. Chame print_maze() para mostrar o estado atual do labirinto
    // 3. Adicione um pequeno atraso para visualização:
    
    // 4. Verifique se a posição atual é a saída (maze[pos.row][pos.col] == 's')
    //    Se for, retorne true
    {
        std::lock_guard<std::mutex> lock(m);
        print_maze();
        if (maze[pos.row][pos.col] == 's')
            return true;
        maze[pos.row][pos.col] = '.';
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // 5. Verifique as posições adjacentes (cima, baixo, esquerda, direita)
    //    Para cada posição adjacente:
    std::vector<Position> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::vector<Position> valid_moves;

    //    a. Se for uma posição válida (use is_valid_position()), adicione-a à pilha valid_positions
    for (int i = 0; i < directions.size(); i++){
        int new_row = pos.row + directions[i].row;
        int new_col = pos.col + directions[i].col;
        if(is_valid_position(new_row, new_col)){
            valid_moves.push_back({new_row, new_col});
        }
    }
    // 6. Enquanto houver posições válidas na pilha (!valid_positions.empty()):
    //    a. Remova a próxima posição da pilha (valid_positions.top() e valid_positions.pop())
    

    // Se houver múltiplos caminhos, crie threads para explorá-los
    for (int i = 1; i < valid_moves.size(); ++i) {
        threads.push_back(std::thread(walk, valid_moves[i]));
    }

    // A thread atual continua a explorar o primeiro caminho
    if (!valid_moves.empty()) {
        return walk(valid_moves[0]);
    }
    //    b. Chame walk recursivamente para esta posição
    //    c. Se walk retornar true, propague o retorno (retorne true)
    // 7. Se todas as posições foram exploradas sem encontrar a saída, retorne false
    
    return false; // Placeholder - substitua pela lógica correta
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_labirinto>" << std::endl;
        return 1;
    }

    Position initial_pos = load_maze(argv[1]);
    if (initial_pos.row == -1 || initial_pos.col == -1) {
        std::cerr << "Posição inicial não encontrada no labirinto." << std::endl;
        return 1;
    }

    bool exit_found = walk(initial_pos);

    // Esperar que todas as threads terminem
    for (std::thread& t : threads) {
        t.join();
    }
    
    if (exit_found) {
        std::cout << "Saída encontrada!" << std::endl;
    } else {
        std::cout << "Não foi possível encontrar a saída." << std::endl;
    }

    return 0;
}

// Nota sobre o uso de std::this_thread::sleep_for:
// 
// A função std::this_thread::sleep_for é parte da biblioteca <thread> do C++11 e posteriores.
// Ela permite que você pause a execução do thread atual por um período especificado.
// 
// Para usar std::this_thread::sleep_for, você precisa:
// 1. Incluir as bibliotecas <thread> e <chrono>
// 2. Usar o namespace std::chrono para as unidades de tempo
// 
// Exemplo de uso:
// std::this_thread::sleep_for(std::chrono::milliseconds(50));
// 
// Isso pausará a execução por 50 milissegundos.
// 
// Você pode ajustar o tempo de pausa conforme necessário para uma melhor visualização
// do processo de exploração do labirinto.
