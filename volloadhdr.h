#ifndef VOLLOADHDR_H
#define VOLLOADHDR_H

#include "volloader.h"
#include <memory>
#include <vector>

namespace yy
{

class VolLoadHDR : public VolLoader
{
public:
    static std::unique_ptr<VolLoadHDR> create(const std::string& filename);
    VolLoadHDR(const std::string& filename);
    virtual ~VolLoadHDR() {}

    virtual std::shared_ptr<Volume> open();

private:
    std::string filename;
    std::vector<int> dimensions;

    std::vector<int> readDimensions() const;
    std::string getDataFilePath() const;
};

} // namespace yy

#endif // VOLLOADHDR_H
