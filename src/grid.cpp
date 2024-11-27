#include "globals.hpp"
#include "grid.hpp"

Grid::Grid(const ui::Dimensions& dimensions, std::string emptyCell_)
    : emptyCell { emptyCell_ },
      rows { dimensions.dimy },
      cols { dimensions.dimx }
{
    this->grid = std::vector(this->rows, std::vector<std::string>(this->cols));
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), this->emptyCell);
    }

    component = ui::Renderer([=] {
        ui::Elements rows {};
        for (int row_i { 0 }; row_i < this->rows; row_i++) {
            ui::Elements row {};
            for (int col_i { 0 }; col_i < this->cols; col_i++) {
                row.push_back(ui::text(this->get(row_i, col_i)));
            }
            rows.push_back(ui::hbox(row));
        }
        return ui::vbox(rows);
    });
}

const std::string& Grid::get(int row, int col) const {
    return grid[row][col];
}

void Grid::set(int row, int col, const std::string& string) {
    grid[row][col] = string;
}

const ui::Component& Grid::getComponent() const {
    return this->component;
}