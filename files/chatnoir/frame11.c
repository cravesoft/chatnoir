// Action script...

// [Action in Frame 11]
function go_out()
{
    var _loc1;
    var _loc5 = catx;
    var _loc4 = caty;
    for (var _loc1 = 0; _loc1 < 6; ++_loc1)
    {
        var _loc3 = _loc4 % 2 ? (_loc5 + addx1[_loc1]) : (_loc5 + addx0[_loc1]);
        var _loc2 = _loc4 + addy0[_loc1];
        if (cel[_loc2][_loc3].stat == 0)
        {
            catx = _loc3;
            caty = _loc2;
            catdir = _loc1;
            return (1);
        } // end if
    } // end of for
    return (0);
} // End of the function
function goto_win()
{
    var _loc5 = catx;
    var _loc4 = caty;
    for (var _loc1 = 0; _loc1 < 6; ++_loc1)
    {
        var _loc3 = _loc4 % 2 ? (_loc5 + addx1[_loc1]) : (_loc5 + addx0[_loc1]);
        var _loc2 = _loc4 + addy0[_loc1];
        if (cel[_loc2][_loc3].stat != 1)
        {
            continue;
        } // end if
        if (cel[_loc2][_loc3].win)
        {
            catx = _loc3;
            caty = _loc2;
            catdir = _loc1;
            return (1);
        } // end if
    } // end of for
    return (0);
} // End of the function
function get_nearest()
{
    var _loc2;
    var _loc6;
    var _loc1;
    var _loc3;
    var _loc11;
    cel[caty][catx].po = 0;
    lx[0] = catx;
    ly[0] = caty;
    var _loc12 = 1;
    var _loc7 = 999;
    for (po = 1; po < 200; po++)
    {
        _loc3 = 0;
        for (var _loc2 = 0; _loc2 < _loc12; ++_loc2)
        {
            var _loc5 = lx[_loc2];
            var _loc4 = ly[_loc2];
            for (var _loc1 = 0; _loc1 < 6; ++_loc1)
            {
                var _loc9 = _loc4 % 2 ? (_loc5 + addx1[_loc1]) : (_loc5 + addx0[_loc1]);
                var _loc8 = _loc4 + addy0[_loc1];
                if (cel[_loc8][_loc9].stat != 1)
                {
                    continue;
                } // end if
                if (cel[_loc8][_loc9].po >= 0)
                {
                    continue;
                } // end if
                cel[_loc8][_loc9].po = po;
                lx2[_loc3] = _loc9;
                ly2[_loc3] = _loc8;
                ++_loc3;
                if (cel[_loc8][_loc9].win && po < _loc7)
                {
                    _loc7 = po;
                } // end if
            } // end of for
        } // end of for
        if (_loc3 == 0)
        {
            break;
        } // end if
        for (var _loc2 = 0; _loc2 < _loc3; ++_loc2)
        {
            lx[_loc2] = lx2[_loc2];
            ly[_loc2] = ly2[_loc2];
        } // end of for
        _loc12 = _loc3;
    } // end of for
    if (_loc7 == 999)
    {
        return (0);
    } // end if
    _loc3 = 0;
    for (var _loc2 = 0; _loc2 < ymax; ++_loc2)
    {
        for (var _loc6 = 0; _loc6 < xmax; ++_loc6)
        {
            if (cel[_loc2][_loc6].po == _loc7 && cel[_loc2][_loc6].win)
            {
                lx[_loc3] = _loc6;
                ly[_loc3] = _loc2;
                ++_loc3;
            } // end if
        } // end of for
    } // end of for
    if (_loc3 == 0)
    {
        return (0);
    } // end if
    _loc11 = Math.floor(Math.random() * _loc3);
    _loc5 = lx[_loc11];
    _loc4 = ly[_loc11];
    for (var _loc10 = 0; _loc10 < 200; ++_loc10)
    {
        _loc3 = 0;
        for (var _loc1 = 0; _loc1 < 6; ++_loc1)
        {
            _loc9 = _loc4 % 2 ? (_loc5 + addx1[_loc1]) : (_loc5 + addx0[_loc1]);
            _loc8 = _loc4 + addy0[_loc1];
            if (cel[_loc8][_loc9].stat != 1)
            {
                continue;
            } // end if
            if (cel[_loc8][_loc9].po >= cel[_loc4][_loc5].po)
            {
                continue;
            } // end if
            lx[_loc3] = _loc9;
            ly[_loc3] = _loc8;
            ld[_loc3] = _loc1;
            ++_loc3;
        } // end of for
        if (_loc3 == 0)
        {
            return (0);
        } // end if
        _loc11 = Math.floor(Math.random() * _loc3);
        _loc5 = lx[_loc11];
        _loc4 = ly[_loc11];
        // la position du chat est trouvée
        if (cel[_loc4][_loc5].po == 1)
        {
            catx = _loc5;
            caty = _loc4;
            catdir = 0;
            // trouve la direction du chat
            for (var _loc1 = 0; _loc1 < 6; ++_loc1)
            {
                _loc9 = _loc4 % 2 ? (_loc5 + addx1[_loc1]) : (_loc5 + addx0[_loc1]);
                _loc8 = _loc4 + addy0[_loc1];
                if (cel[_loc8][_loc9].po == 0)
                {
                    catdir = (_loc1 + 3) % 6;
                } // end if
            } // end of for
            return (1);
        } // end if
    } // end of for
    return (0);
} // End of the function
function rand_move()
{
    var _loc6 = catx;
    var _loc5 = caty;
    var _loc2 = 0;
    for (var _loc1 = 0; _loc1 < 6; ++_loc1)
    {
        var _loc4 = _loc5 % 2 ? (_loc6 + addx1[_loc1]) : (_loc6 + addx0[_loc1]);
        var _loc3 = _loc5 + addy0[_loc1];
        if (cel[_loc3][_loc4].stat != 1)
        {
            continue;
        } // end if
        lx[_loc2] = _loc4;
        ly[_loc2] = _loc3;
        ld[_loc2] = _loc1;
        ++_loc2;
    } // end of for
    if (_loc2 == 0)
    {
        return (0);
    } // end if
    var _loc7 = Math.floor(Math.random() * _loc2);
    catx = lx[_loc7];
    caty = ly[_loc7];
    catdir = ld[_loc7];
    return (1);
} // End of the function
