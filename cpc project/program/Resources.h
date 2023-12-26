#pragma once


#include "Hex.h"


enum Command {
    NONE,
    LOAD_GAME_BOARD
};


enum CommandResult {
    BOARD_STATE_OK,
    WRONG_BLACK_PAWNS_NUMBER,
    WRONG_WHITE_PAWNS_NUMBER,
    WRONG_BOARD_ROW_LENGTH
};


namespace std {
    template<>
    struct hash<Hex> {
        std::size_t operator()(const Hex& h) const {
            std::size_t hq = std::hash<int>{}(h.q);
            std::size_t hr = std::hash<int>{}(h.r);
            std::size_t hs = std::hash<int>{}(h.s);
            return hq ^ (hr << 1) ^ (hs << 2);
        }
    };
}

