//
// Created by Ramil on 12/7/2023.
//

#include "CellGrid.h"

CellGrid::CellGrid(const int width, const int height) : width(width), height(height){
    cells = new Cell*[height];
    for (int y = 0; y < height; y++) {
        cells[y] = new Cell[width];
        for (int x = 0; x < width; x++) {

            cells[y][x] = Cell {
                .x = x,
                .y = y
            };
        }
    }
}

CellGrid::~CellGrid() {
    for (int y = 0; y < height; y++) {
        delete [] cells[y];
    }
    delete [] cells;
}

const std::vector<Cell*> &CellGrid::GetAliveCells() const {
    return aliveCells;
}

Cell CellGrid::GetCell(int x, int y) {
    if (x == -1) {
        x = width - 1;
    }

    if (x == width) {
        x = 0;
    }

    if (y == -1) {
        y = height - 1;
    }

    if (y == height) {
        y = 0;
    }

    if (x < 0 || y < 0 || y > height || x > width) {
        printf("ERROR: Cell is out of bounds, x: %d, y: %d", x, y);
        throw std::exception("Cell is out of bounds");
    }

    return cells[y][x];
}

void CellGrid::AliveCell(int x, int y) {
    cells[y][x] = Cell {
        .alive = true
    };

    aliveCells.push_back(new Cell {
        .x = x,
        .y = y,
        .alive = true
    });
}

void CellGrid::KillCell(int x, int y) {
    cells[y][x] = Cell {
        .alive = false
    };

    int posToDelete = -1;
    int i = 0;
    for (Cell* cell : aliveCells) {
        if (cell->x == x && cell->y == y) {
            posToDelete = i;
            break;
        }

        i++;
    }

    if (posToDelete == -1) {
        printf("ERROR: Can't find a cell to kill, x: %d, y: %d", x, y);
        throw std::exception("Can't find a cell to kill");
    }

    Cell* toFree = aliveCells[posToDelete];
    aliveCells.erase(aliveCells.begin() + posToDelete);
    free(toFree);
}

const int CellGrid::getWidth() const {
    return width;
}

const int CellGrid::getHeight() const {
    return height;
}
