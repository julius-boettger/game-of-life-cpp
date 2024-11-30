#ifndef GRID_HPP
#define GRID_HPP

#include "ftxui/component/component.hpp"

// 2d grid of cells
class Grid {

    unsigned int rows {};
    unsigned int cols {};
    std::string emptyCell {};
    std::vector<std::vector<std::string>> grid {};

    // to render grid using ftxui
    ui::Component component {};

public:

    Grid(const ui::Dimensions& dimensions, std::string emptyCell_);

    const std::string& get(unsigned int row, unsigned int col) const;
    void set(unsigned int row, unsigned int col, const std::string& string);

    unsigned int getRows() const;
    unsigned int getCols() const;

    void update();
    void resize(const ui::Dimensions& dimensions);
    const ui::Component& getComponent() const;
};

#endif