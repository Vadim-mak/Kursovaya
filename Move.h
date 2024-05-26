#pragma once
#ifndef MOVE_H
#define MOVE_H

struct Move {
    int x1, y1, x2, y2;
    bool jump;
    Move(int _x1, int _y1, int _x2, int _y2, bool _jump = false);
};

#endif#pragma once
