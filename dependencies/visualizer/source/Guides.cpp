#include "Guides.h"
#include "Position.h"
#include "Utility.h"

namespace rp::joseph
{
    namespace
    {
        std::vector<Position> createGuides()
        {
            using namespace rp::joseph;
            auto positions = std::vector<Position>();
            for(auto guideFreq : Constants::guideFreqs)
            {
                const auto positionX = normalize(guideFreq);
                positions.emplace_back(Position{positionX, 0.0f, -10.0f});
                positions.emplace_back(Position{positionX, 0.0f, 0.0f});
            }
            return positions;
        }
    }

    Guides::Guides()
    : positions_(createGuides())
    , vbo_(positions_)
    {
    }

    void Guides::bind()
    {
        vbo_.bind();
        vbo_.update(positions_);
    }

    GLsizei Guides::getNumVertices() const
    {
        return static_cast<GLsizei>(positions_.size());
    }
}
