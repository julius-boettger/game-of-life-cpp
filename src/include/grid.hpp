#ifndef GRID_HPP
#define GRID_HPP

#include "ftxui/component/component.hpp"

// 2d grid of cells
class Grid {

    int rows {};
    int cols {};
    std::string emptyCell {};
    std::vector<std::vector<std::string>> grid {};

    // to render grid using ftxui
    ui::Component component {};

public:

    Grid(const ui::Dimensions& dimensions, std::string emptyCell_);

    const std::string& get(int row, int col) const;
    void set(int row, int col, const std::string& string);

    const ui::Component& getComponent() const;
};

#endif