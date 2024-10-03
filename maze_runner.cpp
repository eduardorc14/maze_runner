#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>

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

// Função para carregar o labirinto de um arquivo
Position load_maze(const std::string& file_name) {
    // TODO: Implemente esta função seguindo estes passos:
    // 1. Abra o arquivo especificado por file_name usando std::ifstream
    std::ifstream arquivo(file_name);
    // 6. Trate possíveis erros (arquivo não encontrado, formato inválido, etc.)    
    if(!arquivo.is_open()){
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        return 1;
    }
    if (arquivo.fail() && !arquivo.eof()) {
        std::cerr << "Erro: Formato inválido encontrado no arquivo." << std::endl;
        arquivo.close();
        return 1;
    }
    // 2. Leia o número de linhas e colunas do labirinto
    arquivo >> num_rows >> num_cols;
    // 3. Redimensione a matriz 'maze' de acordo (use maze.resize())
    maze.resize(num_rows);
    for(int i = 0; i < maze.size(); i++){
        maze[i].resize(num_cols);
    }
    // 4. Leia o conteúdo do labirinto do arquivo, caractere por caractere
    std::string linha;
    while (std::getline(arquivo, linha)) { // Lê cada linha do arquivo
        std::vector<char> linha_vec(linha.begin(), linha.end()); // Cria um vetor de char para a linha
        matriz.push_back(linha_vec);
    }
    // 5. Encontre e retorne a posição inicial ('e')
    Position position;
    for(int i = 0; i < maze.size(); i++){
        for(int j = 0; j < maze.size(); j++){
            if(maze[i][j] == "e"){
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
    // TODO: Implemente esta função
    // 1. Percorra a matriz 'maze' usando um loop aninhado
    for(int i = 0; i < maze.size(); i++){
        for(int j = 0; j < maze.size(); j++){
            std::cout << maze[i][j]; // 2. Imprima cada caractere usando std::cout
        }
        std::cout << "\n"; // 3. Adicione uma quebra de linha (std::cout << '\n') ao final de cada linha do labirinto
    }
}

// Função para verificar se uma posição é válida
bool is_valid_position(int row, int col) {
    // TODO: Implemente esta função
    // 1. Verifique se a posição está dentro dos limites do labirinto
    //    (row >= 0 && row < num_rows && col >= 0 && col < num_cols)
    // 2. Verifique se a posição é um caminho válido (maze[row][col] == 'x')
    // 3. Retorne true se ambas as condições forem verdadeiras, false caso contrário

    return false; // Placeholder - substitua pela lógica correta
}

// Função principal para navegar pelo labirinto
bool walk(Position pos) {
    // TODO: Implemente a lógica de navegação aqui
    // 1. Marque a posição atual como visitada (maze[pos.row][pos.col] = '.')
    // 2. Chame print_maze() para mostrar o estado atual do labirinto
    // 3. Adicione um pequeno atraso para visualização:
    //    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // 4. Verifique se a posição atual é a saída (maze[pos.row][pos.col] == 's')
    //    Se for, retorne true
    // 5. Verifique as posições adjacentes (cima, baixo, esquerda, direita)
    //    Para cada posição adjacente:
    //    a. Se for uma posição válida (use is_valid_position()), adicione-a à pilha valid_positions
    // 6. Enquanto houver posições válidas na pilha (!valid_positions.empty()):
    //    a. Remova a próxima posição da pilha (valid_positions.top() e valid_positions.pop())
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
