#include "globals.hpp"
#include "grid.hpp"

Grid::Grid(const ui::Dimensions& dimensions, std::string emptyCell_)
    : rows { static_cast<unsigned int>(dimensions.dimy) },
      cols { static_cast<unsigned int>(dimensions.dimx) },
      emptyCell { emptyCell_ }
{
    this->grid = std::vector(this->rows, std::vector<std::string>(this->cols));
    for (auto& row : this->grid) {
        std::fill(row.begin(), row.end(), this->emptyCell);
    }

    component = ui::Renderer([&] {
        const auto& dims { ui::Dimension::Full() };
        if (static_cast<unsigned int>(dims.dimy) != this->getRows() ||
            static_cast<unsigned int>(dims.dimx) != this->getCols())
        {
            this->resize(dims);
        }

        ui::Elements rows_elems {};
        for (unsigned int row_i { 0 }; row_i < this->rows; row_i++) {
            ui::Elements row_elems {};
            for (unsigned int col_i { 0 }; col_i < this->cols; col_i++) {
                row_elems.push_back(ui::text(this->get(row_i, col_i)));
            }
            rows_elems.push_back(ui::hbox(row_elems));
        }
        return ui::vbox(rows_elems);
    });
}

const std::string& Grid::get(unsigned int row, unsigned int col) const {
    return this->grid[row][col];
}

void Grid::set(unsigned int row, unsigned int col, const std::string& string) {
    this->grid[row][col] = string;
}

unsigned int Grid::getRows() const {
    return this->rows;
}

unsigned int Grid::getCols() const {
    return this->cols;
}

const ui::Component& Grid::getComponent() const {
    return this->component;
}

void Grid::resize(const ui::Dimensions& /*dimensions*/) {
    // TODO set new dimensions, resize grid, center grid
}

bool Grid::isAlive(unsigned int row, unsigned int col) const noexcept {
    if (std::clamp(row, 0u, this->rows - 1) != row ||
        std::clamp(col, 0u, this->cols - 1) != col)
    {
        return false;
    }
    return this->get(row, col) != this->emptyCell;
}

#include <iostream>

void Grid::update() {
    // for every cell
    for (auto row { 0u }; row < this->rows; row++) {
        for (auto col { 0u }; col < this->cols; col++) {
            const auto alive { this->isAlive(row, col) };
            auto aliveNeighbors { 0 };

            // for every neighbor
            for (auto row_offset { -1 }; row_offset <= 1; row_offset++) {
                for (auto col_offset { -1 }; col_offset <= 1; col_offset++) {
                    // skip self
                    if (row_offset == 0 && col_offset == 0) {
                        continue;
                    }

                    if (this->isAlive(
                        static_cast<unsigned int>(static_cast<int>(row) + row_offset),
                        static_cast<unsigned int>(static_cast<int>(col) + col_offset)))
                    {
                        aliveNeighbors++;
                    }
                }
            }

            // kill/revive cell based on number of neighbors
            if (alive && (aliveNeighbors <= 1 || aliveNeighbors >= 4)) {
                this->set(row, col, this->emptyCell);
            } else if (!alive && aliveNeighbors == 3) {
                this->set(row, col, "█");
            }
        }
    }
}