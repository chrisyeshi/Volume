#ifndef VOLLOADFACTORY_H
#define VOLLOADFACTORY_H

#include <memory>
#include <set>
#include <map>
#include <string>
#include <functional>
#include <iostream>
#include <cassert>
#include <QFileInfo>
#include "volloader.h"

namespace yy
{

class VolLoadFactory
{
public:
    typedef std::function<std::unique_ptr<VolLoader>(const std::string&)> CreateFunc;
    static std::set<std::string> extensions();
    static std::unique_ptr<VolLoader> create(const std::string& filename);

private:
    static std::map<std::string, CreateFunc> creators;
};

} // namespace yy

#endif // VOLLOADFACTORY_H
