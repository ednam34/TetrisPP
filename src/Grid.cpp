#include "hpp/Grid.hpp"


    Grid::Grid():actual(),next(){
        grid.resize(GRID_HEIGHT, std::vector<int>(GRID_WIDTH, 0));
        
        //this->actual.turnShape();
        //this->actual.printMatrix();
    

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                grid[i][j + 3] = actual.getMatrix()[i][j];
            }
        }
    }

    void Grid::printGrid(){
        for (int i = 0; i < GRID_HEIGHT; i++) {
            for (int j = 0; j < GRID_WIDTH; j++) {
                std::cout << this->grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }


    void Grid::drawActual(int a, int b){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                grid[i+a][j + b] = actual.getMatrix()[i][j];
            }
        }
        //this->actual.setXY(4,2);
    }


    void Grid::froze(){
        for(int i=GRID_HEIGHT;i>0;i--){
            for(int j=0; j<GRID_WIDTH;j++){
                if(i<GRID_HEIGHT &&  this->grid[i][j]>=1){
                    this->grid[i][j]=grid[i][j]-(2*grid[i][j]);
                }
            }
        }
        //this->printGrid();
        this->lineCheck();
        actual = next;
        next = next.randomPiece();
        actual.setXY(4,0);
        //actual.turnShape();
        drawActual();
    }


    void Grid::turnActual(){
        int x = actual.getX()-1;
        int y = actual.getY()-1;

        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                this->grid[i+y][j+x]=0;
            }
        }
        //std::this_thread::sleep_for(std::chrono::seconds(500));
        
        actual.turnShape();
        this->drawActual(y,x);
        actual.printMatrix();
        //printGrid();
        
    }

    void Grid::lineCheck(){
        if(this->actual.getY()==1){
            this->loose=true;
        }
        for (int i = GRID_HEIGHT - 1; i >= 0; i--) {
            int count =0;
            for (int j = 0; j < GRID_WIDTH; j++) {
                if(grid[i][j] < 0){
                    count++;
                }
                
            }
            if(count==GRID_WIDTH){
                std::cout<<"tu as une ligne !!!"<<std::endl;
                this->deleteLine(i);
                this->score+=10;
            }
        }    
    }


    void Grid::deleteLine(int i){
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j]=0;
        }
        for(int e=i;e>0;e--){
            for (int j = 0; j < GRID_WIDTH; j++) {
            grid[e][j]=grid[e-1][j];
        }
        }
        this->lineCheck();
    }

    void Grid::checkGrid(bool instant) {
        int y = this->actual.getY();

        // Vérifier la portée en fonction de la position Y de la pièce
        int startRow = std::max(y + 1, 0);
        int endRow = std::max(y - 2, -1);

        bool shouldFreeze = false;

        for (int i = startRow; i > endRow; i--) {
            for (int j = 0; j < GRID_WIDTH; j++) {
                if (i >= 0 && i + 1 < GRID_HEIGHT && grid[i][j] >= 1) {
                    if (grid[i + 1][j] != 0) {
                        shouldFreeze = true;
                    } else {
                        grid[i + 1][j] = grid[i][j];
                        grid[i][j] = 0;
                        if ((i + 2 < GRID_HEIGHT && grid[i + 2][j] < 0) || (i + 2 == GRID_HEIGHT)) {
                            shouldFreeze = true;
                        }
                    }
                }
            }
        }

        if (shouldFreeze) {
            froze();
        }

        actual.setY(actual.getY() + 1);

        if(instant && !shouldFreeze){
            checkGrid(true);
        }
    }


    


    void Grid::moveLeft() {
        int x = this->actual.getX();
        int y = this->actual.getY();
        if((grid[this->actual.getY()][this->actual.getX()-1]>=1||grid[this->actual.getY()-1][this->actual.getX()-1]>=1||grid[this->actual.getY()+1][this->actual.getX()-1]>=1||this->actual.getX()-1<0) && this->actual.getX()-2<0){
                return;
        }
         if((grid[y][x - 1] < 0 ) || (grid[y-1][x-1]>0 && grid[y-1][x-2]<0) || (grid[y][x-1]>0 && grid[y][x-2]<0) || (grid[y+1][x-1]>0 && grid[y+1][x-2]<0)){
            return;
        }
        
        
        

        x = actual.getX()-1;
        y = actual.getY()-1;
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){

                if (j+x - 1 >= 0 && grid[i+y][j+x] > 0 && grid[i+y][j+x] <= 7) {
                        std::swap(grid[i+y][j+x], grid[i+y][j+x-1]);
                }

            }
        }


        this->actual.setX(this->actual.getX()-1);
    }

    void Grid::moveRight() {
        int x = this->actual.getX();
        int y = this->actual.getY();
        if ((grid[y][x+ 1] >= 1 || grid[y - 1][x + 1] >= 1 || grid[y + 1][x + 1] >= 1 || x + 1 >= GRID_WIDTH) && (x + 2 >= GRID_WIDTH)) {
            return;
        }

        if((grid[y][x + 1] < 0 ) || (grid[y-1][x+1]>0 && grid[y-1][x+2]<0) || (grid[y][x+1]>0 && grid[y][x+2]<0) || (grid[y+1][x+1]>0 && grid[y+1][x+2]<0)){
            return;
        }
        

        x = actual.getX()-1;
        y = actual.getY()-1;
        for(int i=0;i<SIZE;i++){
            for(int j=SIZE-1;j>=0;j--){

                if (j+x + 1 < GRID_WIDTH && grid[i+y][j+x] > 0) {
                        std::swap(grid[i+y][j+x], grid[i+y][j+x+1]);
                }

            }
        }

        this->actual.setX(this->actual.getX()+1);
    }

    std::vector<std::vector<int>>& Grid::getGrid() {
        return grid;
    }

    int Grid::getScore(){
        return this->score;
    }

    Shape Grid::getAcutal(){
        return this->actual;
    }
    Shape Grid::getNext(){
        return this->next;
    }

    bool Grid::getLoose(){
        return this->loose;
    }

    void Grid::restart(){
        this->loose=false;
        this->score=0;


        for (int i = 0; i < GRID_HEIGHT; i++) {
            for (int j = 0; j < GRID_WIDTH; j++) {
                grid[i][j]=0;
            }
            
        }
        this->drawActual();
    }
