#ifndef VOLLOADRAW_H
#define VOLLOADRAW_H

#include "volloader.h"
#include "volloadfactory.h"
#include <memory>

namespace yy {

class VolLoadRAW : public VolLoader
{
public:
    static std::unique_ptr<VolLoadRAW> create(const std::string& filename);
    VolLoadRAW(const std::string& filename);
    virtual ~VolLoadRAW();

    virtual std::shared_ptr<Volume> open();
    std::shared_ptr<Volume> open(IVolume::ScalarType type, int w, int h, int d);

private:
    std::string filename;
};

} // namespace yy

#endif // VOLLOADRAW_H
