#include "globals.hpp"
#include "grid.hpp"

Grid::Grid(const ui::Dimensions& dimensions, std::string emptyCell_)
    : rows { static_cast<unsigned int>(dimensions.dimy) },
      cols { static_cast<unsigned int>(dimensions.dimx) },
      emptyCell { emptyCell_ }
{
    this->grid = std::vector(this->rows, std::vector<std::string>(this->cols));
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), this->emptyCell);
    }

    component = ui::Renderer([this] {
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
    return grid[row][col];
}

void Grid::set(unsigned int row, unsigned int col, const std::string& string) {
    grid[row][col] = string;
}

const ui::Component& Grid::getComponent() const {
    return this->component;
}