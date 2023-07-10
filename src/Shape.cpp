#include "hpp/Shape.hpp"





Shape::Shape(piece i):p(i){

    this->matrix.resize(3,std::vector<int>(3, 0));
    this->setShape();
}

Shape::Shape(){

    *this = randomPiece();

    this->matrix.resize(3,std::vector<int>(3, 0));
    //std::cout << this->matrix.size() << " je suis la " <<std::endl;
    this->setShape();
}

void Shape::setShape(){
    switch (this->p)
    {
    case I:
        this->matrix[0][1]=1;
        this->matrix[1][1]=1;
        this->matrix[2][1]=1;
        break;
    case J:
        this->matrix[0][1]=2;
        this->matrix[1][1]=2;
        this->matrix[2][1]=2;
        this->matrix[2][0]=2;
        break;
    case L:
        this->matrix[0][1]=3;
        this->matrix[1][1]=3;
        this->matrix[2][1]=3;
        this->matrix[2][2]=3;
        break;
    case T:
        this->matrix[1][1]=4;
        this->matrix[2][0]=4;  
        this->matrix[2][1]=4;
        this->matrix[2][2]=4;
        break; 
    case O:
        this->matrix[0][0]=5;
        this->matrix[0][1]=5;  
        this->matrix[1][0]=5;
        this->matrix[1][1]=5;
        break; 
    case S:
        this->matrix[0][2]=6;
        this->matrix[0][1]=6;
        this->matrix[1][0]=6;  
        this->matrix[1][1]=6;
        break;                
    case Z:
        this->matrix[0][0]=7;
        this->matrix[0][1]=7;  
        this->matrix[1][1]=7;
        this->matrix[1][2]=7;
        break; 

    default:
        this->matrix[0][0]=1;
        this->matrix[0][1]=1;
        this->matrix[2][0]=1;
        break;
    }
    
}


piece Shape::randomPiece() {
    // Initialise le générateur de nombres aléatoires avec une graine basée sur l'horloge du système
    std::mt19937 rng(std::random_device{}());

    // Crée une distribution uniforme pour générer des nombres entiers dans l'intervalle [0, 6]
    std::uniform_int_distribution<int> dist(0, 6);

    // Génère un nombre aléatoire correspondant à l'index d'une pièce
    int index = dist(rng);

    // Retourne la pièce correspondante à l'index
    return static_cast<piece>(index);
}



void Shape::cleanShape(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            this->matrix[i][j]=0;
        }
    }
}

void Shape::turnShape(){
    int size = SIZE;
    std::vector<std::vector<int>> rotatedPiece(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            rotatedPiece[j][size - 1 - i] = matrix[i][j];
        }
    }

    this->matrix=rotatedPiece;
}

void Shape::printMatrix(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << this->matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>>& Shape::getMatrix(){
    return this->matrix;
}

void Shape::SetMatrix(){
    this->matrix.resize(SIZE,std::vector<int>(SIZE, 0));
}

void Shape::setXY(int x, int y){
    this->x=x;
    this->y=y;
}

void Shape::setX(int x){
    this->x=x;
}
void Shape::setY(int y){
    this->y=y;
}
int Shape::getX(){return this->x;}
int Shape::getY(){return this->y;}