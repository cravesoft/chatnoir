// Action script...

// [Action in Frame 12]
for (i = 0; i < ymax; i++)
{
    for (j = 0; j < xmax; j++)
    {
        cel[i][j].reach = 0;
        cel[i][j].po = -1;
    } // end of for
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
            if (cel[ny][nx].win)
            {
                ++cel[i][j].reach;
            } // end if
        } // end of for
    } // end of for
} // end of for
f = 0;
if (go_out() == 0)
{
    if (goto_win() == 0)
    {
        if (get_nearest() == 0)
        {
            if (rand_move() == 0)
            {
                f = 1;
            } // end if
        } // end if
    } // end if
} // end if
if (f)
{
    gotoAndStop("over");
}
else
{
    mcCat.start_jump(catdir);
} // end else if
