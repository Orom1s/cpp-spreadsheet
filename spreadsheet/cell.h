#pragma once

#include "common.h"
#include "formula.h"

#include <functional>
#include <unordered_set>

class Sheet;

class Cell : public CellInterface {
public:
    Cell(Sheet& sheet);
    ~Cell();

    void Set(std::string text);
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;
    std::vector<Position> GetReferencedCells() const override;

    bool IsReferenced() const;

private:
    class Impl;
    class EmptyImpl;
    class TextImpl;
    class FormulaImpl;
    bool WouldIntroduceCircularDependency(const Impl& new_impl) const;
    void InvalidateCacheRecursive(bool force = false);

    std::unique_ptr<Impl> impl_;

    Sheet& sheet_;
    //ячейки от которых зависит текущая ячейка
    std::unordered_set<Cell*> l_nodes_;
    //ячейки которые зависят от текущей ячейки
    std::unordered_set<Cell*> r_nodes_;
};