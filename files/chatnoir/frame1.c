// Action script...

// [Action in Frame 1]
function cat_position()
{
    mc = eval("mcCelLayer.mc_" + caty + "_" + catx);
    mcCat._x = mc._x;
    mcCat._y = mc._y;
    mcCat._visible = true;
} // End of the function
function all_disable()
{
    var i;
    var j;
    for (i = 0; i < ymax; i++)
    {
        for (j = 0; j < xmax; j++)
        {
            if (cel[i][j].stat == 1)
            {
                var mc = eval("mcCelLayer.mc_" + i + "_" + j);
                mc.gotoAndStop(2);
            } // end if
        } // end of for
    } // end of for
} // End of the function
function all_enable()
{
    var i;
    var j;
    for (i = 0; i < ymax; i++)
    {
        for (j = 0; j < xmax; j++)
        {
            var mc = eval("mcCelLayer.mc_" + i + "_" + j);
            if (cel[i][j].stat == 1)
            {
                if (j == catx && i == caty)
                {
                    mc.gotoAndStop(2);
                }
                else
                {
                    mc.gotoAndStop(3);
                } // end else if
                mc._visible = true;
            } // end if
            if (cel[i][j].stat == 2)
            {
                mc.gotoAndStop(4);
                mc._visible = true;
            } // end if
        } // end of for
    } // end of for
} // End of the function
addx0 = [1, 0, -1, -1, -1, 0];
addy0 = [0, 1, 1, 0, -1, -1];
addx1 = [1, 1, 0, -1, 0, 1];
addy1 = [0, 1, 1, 0, -1, -1];
xmax = 15;
ymax = 15;
cel = new Array();
for (i = 0; i < ymax; i++)
{
    cel[i] = new Array();
    for (j = 0; j < xmax; j++)
    {
        cel[i][j] = new Object();
        cel[i][j].stat = 0;
        cel[i][j].win = 0;
    } // end of for
} // end of for
catx = Math.floor(xmax / 2);
caty = Math.floor(ymax / 2);
cel[caty][catx].stat = 1;
lx = new Array();
ly = new Array();
ld = new Array();
lx[0] = catx;
ly[0] = caty;
lmax = 1;
lx2 = new Array();
ly2 = new Array();
for (i = 2; i < ymax - 2; i++)
{
    for (j = 2; j < xmax - 2; j++)
    {
        cel[i][j].stat = 1;
    } // end of for
} // end of for
for (loop = 0; loop < 20; loop++)
{
    rx = Math.floor(Math.random() * xmax);
    ry = Math.floor(Math.random() * ymax);
    if (rx != catx && ry != caty)
    {
        if (cel[ry][rx].stat == 1)
        {
            cel[ry][rx].stat = 2;
        } // end if
    } // end if
} // end of for
for (i = 0; i < ymax; i++)
{
    for (j = 0; j < xmax; j++)
    {
        if (cel[i][j].stat != 1)
        {
            continue;
        } // end if
        for (k = 0; k < 6; k++)
        {
            var nx = i % 2 ? (j + addx1[k]) : (j + addx0[k]);
            var ny = i + addy0[k];
            if (cel[ny][nx].stat == 0)
            {
                cel[i][j].win = 1;
            } // end if
        } // end of for
    } // end of for
} // end of for
w = 34;
h = 26;
opx = -(xmax - 1) * w / 2;
opy = -(ymax - 1) * h / 2;
c = 0;
for (i = 0; i < ymax; i++)
{
    for (j = 0; j < xmax; j++)
    {
        mcName = "mc_" + i + "_" + j;
        mcCelLayer.attachMovie("mcCelOrg", mcName, c);
        mc = eval("mcCelLayer." + mcName);
        mc._x = opx + j * w;
        if (i % 2)
        {
            mc._x = mc._x + w / 4;
        }
        else
        {
            mc._x = mc._x - w / 4;
        } // end else if
        mc._y = opy + i * h;
        mc._visible = false;
        ++c;
    } // end of for
} // end of for
