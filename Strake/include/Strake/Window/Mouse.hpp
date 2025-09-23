#pragma once

namespace Strake {
    struct mouse_t {
        float x;     /*!< X position */
        float y;     /*!< Y position */
        bool left;   /*!< Left button */
        bool right;  /*!< Right button */
        bool middle; /*!< Middle button */
        float wheel; /*!< Wheel */
    };

}